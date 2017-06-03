
#include "keyboard.h"
#include <at89c55.h>

/** Read the key matrix
 *
 * probe each 4 columns to see if a key on one of the 8 rows is pressed
 * @return col*8+row if a key is pressed, -1 otherwise
 */
char readkey() {
    char col;
    
    // row 1
    P3=0b11100000;
    col=readkey_col();
    if (col!=-1) {
        return col;
    }

    // row 2
    P3=0b11010000;
    col=readkey_col();
    if (col!=-1) {
        return col+8;
    }

    // row 3

    P3=0b10110000;
    col=readkey_col();
    if (col!=-1) {
        return col+16;
    }

    // row 4
    P3=0b01110000;
    col=readkey_col();
    if (col!=-1) {
        return col+24;
    }


    return -1;
}

/** Read the columns of the key matrix
 *
 * @return the column number a key is pressed, -1 otherwise
 */
char readkey_col() {

    if (P1_0) return 0;
    if (P1_1) return 1;
    if (P1_2) return 2;
    if (P1_3) return 3;
    if (P1_4) return 4;
    if (P1_5) return 5;
    if (P1_6) return 6;
    if (P1_7) return 7;

    return -1;
}