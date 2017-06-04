#ifndef DISPLAY_H
#define DISPLAY_H

#include "number.h"

#define DIGIT_MINUS 10
#define DIGIT_BLANK 11
#define DIGIT_DOT 16

void display();
void disp_delay();
void disp_init();

void digit_add(unsigned char d);
void disp_mod_exponent();
void disp_move_dot();
void digit_change_sign();

void disp_to_number(__idata t_number *n);

#endif