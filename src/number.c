
#include "number.h"

#define IS_TARGET 1

// n1 <- n1+n2
void number_add(__idata t_number *n1,__idata t_number *n2) {
    __idata unsigned char *ptr1;
    __idata unsigned char *ptr2;
    unsigned char is_positive=1;
    unsigned char i;

    // adjust the exponents
    // TODO

    // sum the mantisses
    mantiss_sum(n1->m,n2->m);

    // normalize the result
    ptr1=n1->m;
    ptr1+=5;
    if (((*ptr1&0xf0)==0)&&(*ptr1)) { //pos
        mantiss_div10(n1->m);
        exponent_inc(n1->e);
    }
    if ((*ptr1&0xf0)==0x90) { //neg
        mantiss_div10(n1->m);
        *ptr1=0x99;
        exponent_inc(n1->e);
    }
    
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

// TODO : overflow
void mantiss_inc(__idata unsigned char *m) {
    unsigned char i;
    unsigned char carry=0;
    (*m)++;
    for(i=0;i<MANTISS_BYTES;i ++) {
        *m+=carry; carry=0;
        if ( (*m&0x0f) >9) *m+=6;
        if ( (*m&0xf0) > 0x90) { *m+=0x60; carry=1;}
        m++;
    }

}

void mantiss_complement(__idata unsigned char *m) {
    unsigned char i;
    __idata unsigned char *ptr=m;
    for(i=0;i<MANTISS_BYTES;i ++) {
        *ptr=0x99-*ptr;
        ptr++;
    }
    mantiss_inc(m);
  //  *(m+5)&=0xf; // 0 on last position
}

unsigned char mantiss_is_negative(__idata unsigned char *m) {
    return *(m+5)?1:0;
}

void mantiss_sum(__idata unsigned char *m1,__idata unsigned char *m2) {
    unsigned char i;
    unsigned char a;
    unsigned char carry=0;

    for(i=0;i<MANTISS_BYTES;i++) {
        //sum
        *m1+=*m2+carry;
      
        //lower nibble
        a=(*m1&0x0f)+(*m2&0x0f)+carry;
        if (a>9) *m1+=0x06;
       
        //upper nibble
        a=(*m1>>4)+(*m2>>4);
        if (a>9) carry=1; else carry=0;

        if (carry) *m1+=0x60;

        m1++;
        m2++;
    }

}

void mantiss_div10(__idata unsigned char *m) {
    unsigned char i;
    for(i=0;i<MANTISS_BYTES;i++) {
        *m>>=4;
        if (i!=(MANTISS_BYTES-1))
            *m|=(*(m+1)&0x0f)<<4;

        m++;
    }
}

// exponent functions
void exponent_set_zero(__idata unsigned char *e) {
    *(e++)=0;
    *e=0;
}

// TODO : overflow
void exponent_inc(__idata unsigned char *e) {
    (*e)++;
    if ( (*e&0x0f)>9) *e+=6;
}

void exponent_complement(__idata unsigned char *e) {
    unsigned char i;
    __idata unsigned char *ptr=e;
    for(i=0;i<EXPONENT_BYTES;i ++) {
        *ptr=0x99-*ptr;
        ptr++;
    }
    exponent_inc(e);
}
