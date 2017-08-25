
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
 unsigned char fn_2nd=0;
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

        if (key==KEY_2ND) {
            fn_2nd^=1;
            continue;
        }

        if (key==KEY_C) {
            // TODO
            continue;
        }

        if (key==KEY_DEGRAD) {
            // TODO
            continue;
        }

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
            case KEY_POW:
            case KEY_INV:
            case KEY_SWP:
            case KEY_DUP:
            case KEY_SQRT:
            case KEY_SIN:
            case KEY_COS:
            case KEY_TAN:
            case KEY_LN:
            case KEY_LOG:
                n=stack_allocate(); 
                disp_to_number(n);
        }

        switch(key) {
            case KEY_ENTER: disp_init();
                break;

            // basic operations
            case KEY_ADD: stack_op_add();
                break;

            case KEY_SUB: stack_op_sub();
                break;

            case KEY_MUL: stack_op_mul();
                break;

            case KEY_DIV: stack_op_div();
                break;

            // advanced operations
            case KEY_POW: // TODO
            case KEY_INV: // TODO
            case KEY_SWP: // TODO
            case KEY_DUP: // TODO
        }

        // keys with 2nd function
        if (!fn_2nd) {
            switch(key) {
                case KEY_SQRT: // TODO
                break;
                case KEY_CONST_PI: // TODO
                break;
                case KEY_SIN: // TODO
                break;
                case KEY_COS: // TODO
                break;
                case KEY_TAN: // TODO
                break;
                case KEY_LN: // TODO
                break;
                case KEY_LOG: // TODO
                break;
            }
        } else {
            switch(key) {
                case KEY_SQR: // TODO
                break;
                case KEY_CONST_E: // TODO
                break;
                case KEY_ASIN: // TODO
                break;
                case KEY_ACOS: // TODO
                break;
                case KEY_ATAN: // TODO
                break;
                case KEY_EXP: // TODO
                break;
                case KEY_10POW: // TODO
                break;
            }
            fn_2nd=0;
        }

        // show the result on the display
        switch(key) {
            case KEY_ADD:
            case KEY_SUB:
            case KEY_MUL:
            case KEY_DIV:
            case KEY_POW:
            case KEY_INV:
            case KEY_SWP:
            case KEY_DUP:
            case KEY_SQRT:
            case KEY_CONST_PI:
            case KEY_SIN:
            case KEY_COS:
            case KEY_TAN:
            case KEY_LN:
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
