
#include "display.h"
#include <at89c55.h>

__data __at(0x20) unsigned char display_mem[12];

__code unsigned char digits[] = {
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

unsigned char *current_digit;
unsigned char digit_counter;
unsigned char *sign_digit;

void display() {

    unsigned char *display = display_mem;
    unsigned char i;

    P2=0x7f;
    P3=0xff;

    i=8;
    do {
        P0=digits[*display];
        display++;
        P2>>=1;
        disp_delay();
    } while (--i!=0);

    i=4;
    P3=0xfe;
    do {
       P0=digits[*display];
       display++; 
       P3<<=1;
       disp_delay();
    } while (--i!=0);

}

void disp_init() {
    unsigned char i;
    for (i=0;i<12;i++) {
        display_mem[i]=DIGIT_BLANK;
    }
    display_mem[8]= (0+DIGIT_DOT);

    current_digit=display_mem+8;
    sign_digit=display_mem;
    digit_counter=8;
}

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


void disp_mod_exponent() {
    current_digit=display_mem+11;
    sign_digit=display_mem+9;
    digit_counter=2;
}

void digit_add(unsigned char d) {

    if(digit_counter==0) return;

    *current_digit=d;
    current_digit--;
    digit_counter--;
}

void digit_change_sign() {
    if (*sign_digit==DIGIT_BLANK)
        *sign_digit=DIGIT_MINUS;
    else
        *sign_digit=DIGIT_BLANK;
}