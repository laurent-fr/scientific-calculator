
#include "display.h"
#include <at89c55.h>

__data __at(0x20) unsigned char display_mem[12]; /** The display memory */

__code unsigned char digits[] = { /** 7 segment digits */
    0b11101010, // 0
	0b00100100, // 1
	0b00101000, // 2
	0b01001010, // 3
	0b00011000, // 4
	0b00010000, // 5
	0b10101010, // 6
	0b00000000, // 7
	0b00001010, // 8
	0b01111110, // 9
    0b00001000, // -
    0b00000000, // ' '
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11101011, // 0.
	0b00100101, // 1.
	0b00101001, // 2.
	0b01001011, // 3.
	0b00011001, // 4.
	0b00010001, // 5.
	0b10101011, // 6.
	0b00000001, // 7.
	0b00001011, // 8.
	0b01111111, // 9.
};

unsigned char *current_digit; /** pointer to the display memory where
    new digits will be put */
unsigned char digit_counter; /** number of digits which can be entered
    before running out of space */
unsigned char *sign_digit; /** pointer to the sign (mantiss or exponent)
    in the display memory */
unsigned char moving_dot; /** flag put to 1 where the dot key is pressed */

/** Display the digits
 *
 * All digits refrenced in display_mem are pushed on the 7 seg. displays
 */
void display() {

    unsigned char *display = display_mem;
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

/** Exponent mode
 *
 * The next digit actions will occurs on the 3 last digits of the display
 */
void disp_mod_exponent() {
    current_digit=display_mem+11;
    sign_digit=display_mem+9;
    digit_counter=2;
    moving_dot=0;
}

/** Add a digit to the display memory
 *
 * All the digits are shifted left (with the dot if moving_dot is TRUE)
 * The new digit d is put on the right position
 */
void digit_add(unsigned char d) {
    char i;

    if(digit_counter==0) return;

    if (sign_digit==display_mem) {
        // mantiss
        for(i=8;i>1;i--) {
            if (moving_dot)
                display_mem[i-1]=display_mem[i];
            else
                display_mem[i-1]=display_mem[i] & 0x0f;
        }
    } else {
        // exponent
        display_mem[10]=display_mem[11];
    }

    *current_digit=d;
    digit_counter--;
}

/** Change the sign
 *
 * Change the sign in position 0 (Mantiss) or position 8 (Exponent)
 */
void digit_change_sign() {
    if (*sign_digit==DIGIT_BLANK)
        *sign_digit=DIGIT_MINUS;
    else
        *sign_digit=DIGIT_BLANK;
}