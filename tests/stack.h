#ifndef STACK_H
#define STACK_H

#include "number.h"

void stack_init();

t_number *stack_allocate();

t_number *stack_peek();

void stack_op_add();
void stack_op_sub();
void stack_op_mul();
void stack_op_div();

#endif