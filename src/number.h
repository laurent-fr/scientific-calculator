#ifndef NUMBER_H
#define NUMBER_H

#define MANTISS_BYTES 5
#define EXPONENT_BYTES 1

typedef struct {
    unsigned char m_sign;
    unsigned char m[MANTISS_BYTES];
    unsigned char e_sign;
    unsigned char e[EXPONENT_BYTES];
} t_number;

void number_add(t_number *n1,t_number *n2);
void number_sub(t_number *n1,t_number *n2);
void number_mul(t_number *n1,t_number *n2);
void number_div(t_number *n1,t_number *n2);

#endif