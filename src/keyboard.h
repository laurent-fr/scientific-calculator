#ifndef KEYBOARD_H
#define KEYBOARD_H

// row 1
#define KEY_2ND 0
#define KEY_r1c2 1
#define KEY_r1c3 2
#define KEY_r1c4 3
#define KEY_7 4
#define KEY_8 5
#define KEY_9 6
#define KEY_r1c8 7

// row 2
#define KEY_r2c1 8
#define KEY_r2c2 9
#define KEY_r2c3 10
#define KEY_r2c4 11
#define KEY_4 12
#define KEY_5 13
#define KEY_6 14
#define KEY_r2c8 15

// row 3
#define KEY_r3c1 16
#define KEY_r3c2 17
#define KEY_r3c3 18
#define KEY_r3c4 19
#define KEY_1 20
#define KEY_2 21
#define KEY_3 22
#define KEY_E 23

// row 4
#define KEY_r4c1 24
#define KEY_r4c2 25
#define KEY_r4c3 26
#define KEY_r4c4 27
#define KEY_0 28
#define KEY_DOT 29
#define KEY_SIGN 30
#define KEY_ENTER 31

char readkey();
char readkey_col();


#endif