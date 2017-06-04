
#include "number.h"

#define IS_TARGET 1

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
    (*m)++;
    mantiss_da(m);
}

void mantiss_complement(__idata unsigned char *m) {
    int i;
    __idata unsigned char *ptr=m;
    for(i=0;i<MANTISS_BYTES;i ++) {
        *ptr=0x99-*ptr;
        ptr++;
    }
    mantiss_inc(m);
}

void mantiss_da(__idata unsigned char *m) __naked {

// TODO : carry ...
#ifdef IS_TARGET
    m;

    __asm
    push ar0
    push ar6
    mov r0,dpl
    mov r6,#6
    mantiss_da_loop$:
    mov a,r0
    da a 
    mov r0,a
    djnz r6,mantiss_da_loop$
    pop ar6
    pop ar0
    ret
    __endasm;

#else

    int i;
    unsigned char carry=0;
    for(i=0;i<MANTISS_BYTES;i++) {
        *m+=carry;
        if ((*m&0xf)>9) *m+=6;
        if ((*m&0xf0)>0x90) { *m+=0x60; carry=1; } else carry=0;
        m++;
    }

#endif

}


// exponent functions
void exponent_set_zero(__idata unsigned char *e) {
    *(e++)=0;
    *e=0;
}

void exponent_inc(__idata unsigned char *e) {
    (*e)++;
    exponent_da(e);
}

void exponent_complement(__idata unsigned char *e) {
    int i;
    __idata unsigned char *ptr=e;
    for(i=0;i<EXPONENT_BYTES;i ++) {
        *ptr=0x99-*ptr;
        ptr++;
    }
    exponent_inc(e);
}

void exponent_da(__idata unsigned char *e) __naked {

#ifdef IS_TARGET

    e;

   __asm
    push ar0
    push ar6
    mov r0,dpl
    mov r6,#2
    exponent_da_loop$:
    mov a,r0
    da a
    mov r0,a
    djnz r6,exponent_da_loop$
    pop ar6
    pop ar0
    ret
    __endasm;

#else

 int i;
    for(i=0;i<EXPONENT_BYTES;i++) {
        if ((*e&0xf)>9) *e+=6;
        e++;
    }

#endif

}
