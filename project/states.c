#include "states.h"
#include "leds.h"
#include "sounds.h"

extern volatile int current_state;

void switch_state(int state) {
    switch(state) {
        case 0:
            red_on();
            green_off();
            break;
        case 1:
            red_off();
            green_on();
            break;
        case 2:
            red_on();
            green_on();
            break;
        case 3:
            red_off();
            green_off();
            break;
    }
}

