
#include "display.h"
#include "keyboard.h"


void init() {
    disp_init();
}

void loop() {
 char key;
    
    display();
    key = readkey();

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
    }
}


void main() {

    init();
    while(1) loop();

}
