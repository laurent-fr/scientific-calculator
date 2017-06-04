
#include "stack.h"

#define STACK_SIZE 16
#define STACK_ADDR 0x80

t_number stack[STACK_SIZE];
t_number *stack_ptr;

void stack_init() {
    stack_ptr=0;
}

t_number *stack_allocate() {
    if (stack_ptr==0) {
        stack_ptr=stack;
        return stack_ptr;
    }

    // TODO : stack overflow

    stack_ptr++;
    return stack_ptr;
}

t_number *stack_peek() {
    return stack_ptr;
}

// TODO : stack empty ...
void stack_op_add() {
    t_number *ptr=stack_ptr-1;
    number_add(ptr,stack_ptr);
    stack_ptr=ptr;
}

void stack_op_sub() { 
}

void stack_op_mul() { 
}

void stack_op_div() { 
}