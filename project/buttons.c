#include <msp430.h>
#include "buttons.h"

extern volatile int current_state;

void buttons_init() {
    P2DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3); // P2.0–3 as input
    P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);  // Enable resistors
    P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);  // Pull-up resistors
    P2IE  |= (BIT0 | BIT1 | BIT2 | BIT3);  // Enable interrupts
    P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);  // Falling edge
    P2IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3); // Clear flags
}

// Called from ISR
void button_pressed(char button_index) {
    current_state = (current_state + 1) % 4;
}
