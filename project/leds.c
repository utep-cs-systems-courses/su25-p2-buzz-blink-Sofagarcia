#include <msp430.h>
#include "leds.h"

void led_init() {
    P1DIR |= BIT0 | BIT6; // Green (P1.6) + Red (P1.0)
    P1OUT &= ~(BIT0 | BIT6); //both leds off initially
    
    P1SEL |= BIT6;        // Green LED uses PWM
    P1SEL2 &= ~BIT6;

    TA0CCR0 = 1000;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = 500;
    TA0CTL = TASSEL_2 + MC_1;
}

void set_led_blink(unsigned int rate) {
    TA0CCR0 = rate;
    TA0CCR1 = rate / 2;
}

void set_led_brightness(unsigned int level) {
    TA0CCR1 = level;
}

void leds_off() {
    TA0CCR1 = 0;    //Green off
    P1OUT &= ~BIT0; // turn off red 
}

void red_on() {
    P1OUT |= BIT0;
}

void red_off() {
    P1OUT &= ~BIT0;
}

void green_on() {
  TA0CCR1 = TA0CCR0 / 2; //50% brightness
}

void green_off(){
  TA0CCR1 = 0;
}
