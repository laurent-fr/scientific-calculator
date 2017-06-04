
#include "display.h"
#include "number.h"

#define IS_TARGET 1

#ifdef IS_TARGET
#include <at89c55.h>
#endif

/* The display is made of 12*7 seg. :
 * [S][M][M][M][M][M][M][M][M][S][E][E]
 * S: sign, M: mantiss, E: exponent
 *
 * The display is multiplexed :
 *  - the segments are on P0 (bit LOW = segment ON)
 *  - digits 0 to 7 are activated by a LOW state on P2_7 to P2_0
 *  - digits 8 to 11 are activated by a LOW state on P3_0 to P3_3
 */


__data __at(0x20) unsigned char display_mem[12]; /** The display memory */

__code unsigned char digits[] = { /** 7 segment digits */
    0b11101011, // 0
	0b00100101, // 1
	0b00101001, // 2
	0b01001011, // 3
	0b00011001, // 4
	0b00010001, // 5
	0b10101011, // 6
	0b00000001, // 7
	0b00001011, // 8
	0b01111111, // 9
    0b00001001, // -
    0b11111111, // ' '
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11101010, // 0.
	0b00100100, // 1.
	0b00101000, // 2.
	0b01001010, // 3.
	0b00011000, // 4.
	0b00010000, // 5.
	0b10101010, // 6.
	0b00000000, // 7.
	0b00001010, // 8.
	0b01111110, // 9.
};

__data unsigned char *current_digit; /** pointer to the display memory where
    new digits will be put */
unsigned char digit_counter; /** number of digits which can be entered
    before running out of space */
__data unsigned char *sign_digit; /** pointer to the sign (mantiss or exponent)
    in the display memory */
unsigned char moving_dot; /** flag put to 1 where the dot key is pressed */


/** Init the display memory
 *
 * The memory contains '       0.   '
 */
void disp_init() {
    unsigned char i;
    for (i=0;i<12;i++) {
        display_mem[i]=DIGIT_BLANK;
    }
    display_mem[8]= (0+DIGIT_DOT);

    current_digit=display_mem+8;
    sign_digit=display_mem;
    digit_counter=8;
    moving_dot=0;
}

/** Display the digits
 *
 * All digits refrenced in display_mem are pushed on the 7 seg. displays
 */
#ifdef IS_TARGET
void disp_do_display() {

    __data unsigned char *display = display_mem;
    unsigned char i;

    P2=0x7f;
    P3=0xff;

    i=8;
    do {
        P0=digits[*display];
        display++;
        disp_delay();
        P0=0;
        P2 = P2>>1 | 0x80;  
    } while (--i!=0);

    i=4;
    P3=0xfe;
    do {
       P0=digits[*display];
       display++; 
       disp_delay();
       P0=0;
       P3 = P3<<1 | 0x01;
    } while (--i!=0);

}
#endif

/** Dot key action
 *
 */
void disp_move_dot() {
    moving_dot=1;
}

/** Delay function
 *
 * A small delay for the display function , rougly 100hz for whole display
 */
 #ifdef IS_TARGET
void disp_delay() __naked {

__asm
    push ar7
    mov r7,#120
disp_delay_loop:
    djnz r7,disp_delay_loop
    pop ar7
    ret
__endasm;

}
#endif 

/** Exponent mode
 *
 * The next digit actions will occurs on the 3 last digits of the display
 */
void disp_mod_exponent() {
    current_digit=display_mem+10;
    *(current_digit++)=0;
    *current_digit=0; // current_digit <- display_mem+11
    sign_digit=display_mem+9;
    digit_counter=2;
    moving_dot=0;
}

/** Add a digit to the display memory
 *
 * All the digits are shifted left (with the dot if moving_dot is TRUE)
 * The new digit d is put on the right position
 */
void disp_add_digit(unsigned char d) {
    char i;

    if(digit_counter==0) return;

    if (sign_digit==display_mem) {
        // mantiss
        for(i=1;i<8;i++) {
            if (moving_dot)
                display_mem[i]=display_mem[i+1];
            else
                display_mem[i]=(display_mem[i]&0xf0) | (display_mem[i+1] & 0x0f);
        }
    } else {
        // exponent
        display_mem[10]=display_mem[11];
    }

    if (moving_dot)
        *current_digit=d;
    else
        *current_digit=(*current_digit&0xf0) | d;

    digit_counter--;
}

/** Change the sign
 *
 * Change the sign in position 0 (Mantiss) or position 8 (Exponent)
 */
void disp_change_sign() {
    if (*sign_digit==DIGIT_BLANK)
        *sign_digit=DIGIT_MINUS;
    else
        *sign_digit=DIGIT_BLANK;
}

/** Convert the data in the display memory to a number
 *
 * Display : Sm M8 M7 M6 M5 M4 M3 M2 M1 Se E2 E1
 * Number format : 
 *     Mantiss  -> [0,0] [M2,M1] [M4,M3] [M6,M5] [M8,M7] [0,Sm]
 *     Exponent -> [E2,E1] [0,Se]
 */
void disp_to_number(__idata t_number *n) {
    unsigned char i;
    unsigned char dot_pos=0;
    __idata unsigned char *ptr;

    // set the exponent if blank
    if (display_mem[11]==DIGIT_BLANK) {
        display_mem[10]=0;
        display_mem[11]=0;
    }
	
    // align the mantiss to the left of the display
    while(display_mem[1]==DIGIT_BLANK) {
        for(i=1;i<8;i++) {
            display_mem[i]=display_mem[i+1];
        }
        display_mem[8]=0;
    }

    // pack the display data to the number
    ptr=n->m;
    *(ptr++)=0x00;
    for(i=8;i>0;i-=2) *(ptr++)=((display_mem[i]&0x0f)<<4)|(display_mem[i-1]&0x0f);
    *(ptr++)=0x00;
    ptr=n->e;
    *(ptr++)=(display_mem[10]<<4)|display_mem[11];
    *ptr=0x00;

    // find the dot
    for(i=1;i<9;i++) {
        if (display_mem[i]&0x10) { dot_pos=i; break; }
    }

    // the mantiss must be in the intervall ]-10;10[ , so adjust the exponent
    while (dot_pos>1) {
        exponent_inc(n->e);
        dot_pos --;
    }

    // take care of the sign
    if (display_mem[0]==DIGIT_MINUS) mantiss_complement(n->m);
    if (display_mem[9]==DIGIT_MINUS) exponent_complement(n->e);
}