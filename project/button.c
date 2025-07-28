#include <msp430.h>
#include "buttons.h"

extern volatile int current_state;

void buttons_init() {
    P2DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);
    P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);
    P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);
    P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);
    P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);
    P2IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3);
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    if (P2IFG & BIT0) {
        current_state = 1;
        P2IFG &= ~BIT0;
    } else if (P2IFG & BIT1) {
        current_state = 2;
        P2IFG &= ~BIT1;
    } else if (P2IFG & BIT2) {
        current_state = 0;
        P2IFG &= ~BIT2;
    }
}
