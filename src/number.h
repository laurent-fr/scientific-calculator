#ifndef NUMBER_H
#define NUMBER_H

#define MANTISS_DIGITS 10
#define EXPONENT_DIGITS 2
#define MANTISS_BYTES 6
#define EXPONENT_BYTES 2
#define NUMBER_SIZE (MANTISS_BYTES+EXPONENT_BYTES)

typedef struct {
    unsigned char m[MANTISS_BYTES];
    unsigned char e[EXPONENT_BYTES];
} t_number;

// number functions
void number_add(__idata t_number *n1,__idata t_number *n2);
void number_sub(__idata t_number *n1,__idata t_number *n2);
void number_mul(__idata t_number *n1,__idata t_number *n2);
void number_div(__idata t_number *n1,__idata t_number *n2);

void number_copy(__idata t_number *n1,__idata t_number *n2);

// mantiss functions
void mantiss_set_zero(__idata unsigned char *m);
unsigned char mantiss_is_zero(__idata unsigned char *m);
void mantiss_inc(__idata unsigned char *m);
void mantiss_complement(__idata unsigned char *m);
unsigned char mantiss_is_negative(__idata unsigned char *m);
void mantiss_div10(__idata unsigned char *m);
void mantiss_add(__idata unsigned char *m1,__idata unsigned char *m2);
void mantiss_copy(__idata unsigned char *m1,__idata unsigned char *m2);

// exponent functions
void exponent_set_zero(__idata unsigned char *e);
unsigned char exponent_is_zero(__idata unsigned char *e);
void exponent_inc(__idata unsigned char *e);
void exponent_dec(__idata unsigned char *e);
void exponent_complement(__idata unsigned char *e);
unsigned char exponent_is_negative(__idata unsigned char *e);
void exponent_add(__idata unsigned char *e1,__idata unsigned char *e2);
void exponent_sub(__idata unsigned char *e1,__idata unsigned char *e2);
void exponent_copy(__idata unsigned char *e1,__idata unsigned char *e2);

#endif