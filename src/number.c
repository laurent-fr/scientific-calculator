
#include "number.h"

// n1 <- n1+n2
void number_add(__idata t_number *n1,__idata t_number *n2) {
    n1;
    n2;
}

// n1 <- n1-n2
void number_sub(__idata t_number *n1,__idata t_number *n2) {
    n1;
    n2;
}

// n1 <- n1*n2
void number_mul(__idata t_number *n1,__idata t_number *n2) {
    n1;
    n2;
}

// n1 <- n1/n2
void number_div(__idata t_number *n1,__idata t_number *n2) {
    n1;
    n2;
}

// mantiss functions
void mantiss_set_zero(__idata unsigned char *m) {
    unsigned char i;
    for(i=0;i<6;i++) *(m++)=0;
}

unsigned char mantiss_is_zero(__idata unsigned char *m) {
    unsigned char i;
    for(i=0;i<5;i++) if (*(m++)) return 0;
    return 1;
}

void mantiss_inc(__idata unsigned char *m) {
    *m++;
    mantiss_da(m);
}

void mantiss_complement(__idata unsigned char *m) {
    m;
}

void mantiss_da(__idata unsigned char *m) __naked {

    m;

    __asm
    push ar0
    push ar6
    mov r0,dpl
    mov r6,#6
    mantiss_da_loop:
    mov a,r0
    da a
    mov r0,a
    djnz r6,mantiss_da_loop
    pop ar6
    pop ar0
    ret
    __endasm;
}


// exponent functions
void exponent_set_zero(__idata unsigned char *e) {
    *(e++)=0;
    *e=0;
}

void exponent_inc(__idata unsigned char *e) {
    *e++;
    exponent_da(e);
}

void exponent_complement(__idata unsigned char *e) {
    e;
}

void exponent_da(__idata unsigned char *e) __naked {

    e;

   __asm
    push ar0
    push ar6
    mov r0,dpl
    mov r6,#2
    exponent_da_loop:
    mov a,r0
    da a
    mov r0,a
    djnz r6,exponent_da_loop
    pop ar6
    pop ar0
    ret
    __endasm;
}
