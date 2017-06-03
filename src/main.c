
#include "display.h"
#include "keyboard.h"

#include "number.h"

void init() {
    disp_init();
}

void loop() {
 char key;

    // wait until no key is pressed
    while (readkey()!=-1) {
        display();
    }
    disp_delay();
    
    // wait for a key
    do {
        display();
        key = readkey();

        if (key==-1) continue;

        switch(key) {

            // number
            case KEY_0: digit_add(0); break;
            case KEY_1: digit_add(1); break;
            case KEY_2: digit_add(2); break;
            case KEY_3: digit_add(3); break;
            case KEY_4: digit_add(4); break;
            case KEY_5: digit_add(5); break;
            case KEY_6: digit_add(6); break;
            case KEY_7: digit_add(7); break;
            case KEY_8: digit_add(8); break;
            case KEY_9: digit_add(9); break;
            case KEY_DOT: disp_move_dot(); break;
            case KEY_E: disp_mod_exponent(); break;
            case KEY_SIGN: digit_change_sign(); break;
        }

    } while(key==-1);
}


void main() {

    init();
    while(1) loop();

}
