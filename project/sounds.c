#include <msp430.h>
#include "sounds.h"

void sound_init() {
    P2DIR |= BIT6;
    P2SEL |= BIT6;
    TA1CCR0 = 1000;
    TA1CCTL1 = OUTMOD_7;
    TA1CCR1 = 500;
    TA1CTL = TASSEL_2 + MC_1;
}

void set_sound(unsigned int freq) {
    TA1CCR0 = freq;
    TA1CCR1 = freq / 2;
}

void sound_off() {
    TA1CCR1 = 0;
}
