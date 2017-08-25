#ifndef ERROR_H
#define ERROR_H

#define ERR_OVERFLOW 0
#define ERR_DIV_BY_ZERO 1
#define ERR_STACK_EMPTY 2
#define ERR_STACK_FULL 3
#define ERR_UNDEFINED 4
#define ERR_NO_ERROR 255

void error_set(unsigned char err);
unsigned char error_get();
unsigned char error_get_digit(unsigned char digit);

#endif