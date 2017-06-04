
#include "stack.h"

#define STACK_SIZE 16
#define STACK_ADDR

__idata __at(STACK_ADDR) t_number stack[STACK_SIZE];


__idata t_number *stack_allocate() {

}