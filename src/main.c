
#include "display.h"
#include "keyboard.h"

#include "stack.h"

void init() {
    disp_init();
    stack_init();
}

void loop() {
 char key;

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

            // number
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
        }

    } while(key==-1);
}


void main() {

    init();
    while(1) loop();

}
