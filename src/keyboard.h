#ifndef KEYBOARD_H
#define KEYBOARD_H

// row 1
#define KEY_2ND 0
#define KEY_PI 1
#define KEY_E 1 // 2nd
#define KEY_SQRT 2
#define KEY_SQR 2 // 2nd
#define KEY_7 3
#define KEY_8 4
#define KEY_9 5
#define KEY_DIV 6
#define KEY_C 7

// row 2
#define KEY_SIN 8
#define KEY_ASIN 8 // 2nd
#define KEY_COS 9
#define KEY_ACOS 8 // 2nd
#define KEY_TAN 10
#define KEY_ATAN 10 // 2nd
#define KEY_4 11
#define KEY_5 12
#define KEY_6 13
#define KEY_MUL 14
#define KEY_DEGRAD 15

// row 3
#define KEY_POW 16
#define KEY_LN 17
#define KEY_EXP 17 // 2nd
#define KEY_LOG 18
#define KEY_10POW 18 // 2nd
#define KEY_1 19
#define KEY_2 20
#define KEY_3 21
#define KEY_SUB 22
#define KEY_E 23

// row 4
#define KEY_INV 24
#define KEY_SWP 25
#define KEY_DUP 26
#define KEY_0 27
#define KEY_DOT 28
#define KEY_SIGN 29
#define KEY_ADD 30
#define KEY_ENTER 31

char kbd_readkey();

#endif