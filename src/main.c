
#include "display.h"
#include "keyboard.h"

#include "stack.h"

void init() {
    disp_init();
    stack_init();
}

void loop() {
 char key;
 unsigned char must_init_display=0;

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
            case KEY_0:
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
            case KEY_DOT:
            case KEY_E:
            case KEY_SIGN:
                if (must_init_display) disp_init();
        }

        switch(key) {
            // enter a number
            case KEY_0: disp_add_digit(0); continue;
            case KEY_1: disp_add_digit(1); continue;
            case KEY_2: disp_add_digit(2); continue;
            case KEY_3: disp_add_digit(3); continue;
            case KEY_4: disp_add_digit(4); continue;
            case KEY_5: disp_add_digit(5); continue;
            case KEY_6: disp_add_digit(6); continue;
            case KEY_7: disp_add_digit(7); continue;
            case KEY_8: disp_add_digit(8); continue;
            case KEY_9: disp_add_digit(9); continue;
            case KEY_DOT: disp_move_dot(); continue;
            case KEY_E: disp_mod_exponent(); continue;
            case KEY_SIGN: disp_change_sign(); continue;
        }

        switch(key) {
            // push a new number on the stack
            case KEY_ENTER:
            case KEY_ADD:
            case KEY_SUB:
            case KEY_MUL:
            case KEY_DIV:
                n=stack_allocate(); 
                disp_to_number(n);
        }

        switch(key) {
            case KEY_ENTER: 
                disp_init();
                break;

            // basic operations
            case KEY_ADD:
                stack_op_add();

            case KEY_SUB:
                stack_op_sub();

            case KEY_MUL:
                stack_op_mul();

            case KEY_DIV:
                stack_op_div();
        }

        switch(key) {
            case KEY_ADD:
            case KEY_SUB:
            case KEY_MUL:
            case KEY_DIV:
                disp_from_number(stack_peek());
                must_init_display=1;
                break;
        }
            

    } while(key==-1);
}


void main() {

    init();
    while(1) loop();

}
