
#include "display.h"
#include "keyboard.h"

#include "stack.h"

void init() {
    disp_init();
    stack_init();
}

void loop() {
 char key;
 __idata t_number *n;

    // wait until no key is pressed
    while (kbd_readkey()!=-1) {
        disp_do_display();
    }
    disp_delay();

    // wait for a key
    do {
        disp_do_display();
        key = kbd_readkey();

        if (key==-1) continue;

        switch(key) {

            // enter a number
            case KEY_0: disp_add_digit(0); break;
            case KEY_1: disp_add_digit(1); break;
            case KEY_2: disp_add_digit(2); break;
            case KEY_3: disp_add_digit(3); break;
            case KEY_4: disp_add_digit(4); break;
            case KEY_5: disp_add_digit(5); break;
            case KEY_6: disp_add_digit(6); break;
            case KEY_7: disp_add_digit(7); break;
            case KEY_8: disp_add_digit(8); break;
            case KEY_9: disp_add_digit(9); break;
            case KEY_DOT: disp_move_dot(); break;
            case KEY_E: disp_mod_exponent(); break;
            case KEY_SIGN: disp_change_sign(); break;

            // push a new number on the stack
            case KEY_ENTER: 
                n=stack_allocate(); 
                disp_to_number(n);
                disp_init();
                break;

            // basic operations
            case KEY_ADD:
                stack_op_add();
                disp_from_number(stack_peek());
                break;

            case KEY_SUB:
                stack_op_sub();
                disp_from_number(stack_peek());
                break;

            case KEY_MUL:
                stack_op_mul();
                disp_from_number(stack_peek());
                break;

            case KEY_DIV:
                stack_op_div();
                disp_from_number(stack_peek());
                break;
        }

    } while(key==-1);
}


void main() {

    init();
    while(1) loop();

}
