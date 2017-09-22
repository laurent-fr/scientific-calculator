
#include "stack.h"
#include "constants.h"

#define STACK_SIZE 16
#define STACK_ADDR 0x80

__idata __at(STACK_ADDR) t_number stack[STACK_SIZE];
__idata t_number *stack_ptr;


void stack_init() {
    stack_ptr=0;
}

__idata t_number *stack_allocate() {
    if (stack_ptr==0) {
        stack_ptr=stack;
        return stack_ptr;
    }

    // TODO : stack overflow

    stack_ptr++;
    return stack_ptr;
}

__idata t_number *stack_peek() {
    return stack_ptr;
}

unsigned char stack_is_full() {
 // TODO
}

unsigned char stack_is_empty() {
 // TODO
}

// TODO : stack empty ...
void stack_op_add() {
    __idata t_number *ptr=stack_ptr-1;
    number_add(ptr,stack_ptr);
    stack_ptr=ptr;
}

void stack_op_sub() { 
    __idata t_number *ptr=stack_ptr-1;
    mantiss_complement(stack_ptr->m);
    number_add(ptr,stack_ptr);
    stack_ptr=ptr;
}


void stack_op_mul() { 
    __idata t_number *ptr=stack_ptr-1;
    mantiss_complement(stack_ptr->m);
    number_mul(ptr,stack_ptr);
    stack_ptr=ptr;
}

void stack_op_div() { 
    __idata t_number *ptr=stack_ptr-1;
    mantiss_complement(stack_ptr->m);
    number_div(ptr,stack_ptr);
    stack_ptr=ptr;
}

void stack_op_const_pi() {
    __idata t_number *n;
    n=stack_allocate();
    number_copy_constant(n,constant_get(CONST_PI));
}