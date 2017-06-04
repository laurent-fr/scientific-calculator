
#include "stack.h"

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