//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS; //set bits to output
  //turn off green light, on red light 
  //P1OUT &= ~LED_GREEN;
  //P1OUT |= LED_RED;

  //turn off red and on green leds
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;

  //turn off red and green leds
  //P1OUT &= ~LED_GREEN;
  //P1OUT &= ~LED_RED;

  //turn on both red and green leds
  //P1OUT |= LED_GREEN;
  //P1OUT |= LED_RED;

  or_sr(0x18);		/* CPU off, GIE on */
}
