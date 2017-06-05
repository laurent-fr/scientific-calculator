
#include "number.h"

#define IS_TARGET 1

// n1 <- n1+n2
void number_add(__idata t_number *n1,__idata t_number *n2) {
    __idata unsigned char *ptr1;
    __data unsigned char tmp_e1[EXPONENT_BYTES];
    __data unsigned char tmp_e2[EXPONENT_BYTES];

   // n2 is zero
   if (mantiss_is_zero(n2->m)) return;

   // n1 is zero
   if (mantiss_is_zero(n1->m)) {
       number_copy(n1,n2);
       return;
   }

    // adjust the exponents
    exponent_copy(tmp_e1,n1->e);
    exponent_copy(tmp_e2,n2->e);
    exponent_sub(tmp_e1,tmp_e2);

    if (*tmp_e1) { // e1<>e2
         
        if (!tmp_e1[1]) { // e1>e2

            if (*tmp_e1>MANTISS_DIGITS) // exponent difference > number of mantiss digits
                return;

                // align n2 mantiss 
            while(tmp_e1[0]) {
                mantiss_div10(n2->m);
                exponent_inc(n2->m);
                tmp_e1[0]--;
            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
        } else { // e2>e1

            exponent_complement(tmp_e1);  // |e2-e1|

            if (*tmp_e1>MANTISS_DIGITS) { // exponent difference > number of mantiss digits
                number_copy(n1,n2);
                return;
            }

            // align n1 mantiss 
            while(tmp_e1[0]--) {           
                mantiss_div10(n1->m);
                exponent_inc(n1->e);
            }
        }             
    }
   
    // sum the mantisses
    mantiss_add(n1->m,n2->m);

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
    mantiss_complement(n2->m);
    number_add(n1,n2);
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

void number_copy(__idata t_number *n1,__idata t_number *n2) {
    mantiss_copy(n1->m,n2->m);
    exponent_copy(n1->e,n2->e);
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

void mantiss_add(__idata unsigned char *m1,__idata unsigned char *m2) {
    unsigned char i;
    unsigned char a;
    unsigned char carry=0;

    for(i=0;i<MANTISS_BYTES;i++) {
        //lower nibble
        a=(*m1&0x0f)+(*m2&0x0f)+carry;
        if (a>9) *m1+=0x06;

        //sum
        *m1+=*m2+carry;    
       
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

void mantiss_copy(__idata unsigned char *m1,__idata unsigned char *m2) {
    unsigned char i;
    for(i=0;i<MANTISS_BYTES;i++) *(m1++)=*(m2++);
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

void exponent_copy(__idata unsigned char *e1,__idata unsigned char *e2) {
    *(e1++)=*(e2++);
    *e1=*e2;
}

void exponent_add(__idata unsigned char *e1,__idata unsigned char *e2) {
    unsigned char i;
    unsigned char a;
    unsigned char carry=0;

    for(i=0;i<EXPONENT_BYTES;i++) {

        //lower nibble
        a=(*e1&0x0f)+(*e2&0x0f)+carry;
        if (a>9) *e1+=0x06;

        //sum
        *e1+=*e2+carry;

        //upper nibble
        a=(*e1>>4);
        if (a>9) carry=1; else carry=0;
        if (carry) *e1+=0x60;
        e1++;
        e2++;
    }


}

void exponent_sub(__idata unsigned char *e1,__idata unsigned char *e2) {
    exponent_complement(e2);
    exponent_add(e1,e2);
}