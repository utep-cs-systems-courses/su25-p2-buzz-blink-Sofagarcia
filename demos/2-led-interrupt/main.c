//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

short timeCounter = 0;

void advance_250th(){
  timeCounter++;

  switch(timeCounter){
  case 250:
    P1OUT = (P1OUT & ~LEDS) | LED_GREEN; //green only
    break;
  case 500:
    P1OUT = (P1OUT & ~LEDS) | LED_RED; // red only
    break;
  case 750:
    P1OUT = (P1OUT & ~LEDS) | (LED_RED | LED_GREEN); //both
    break;
  case 1000:
    P1OUT &= ~LEDS; //both but off
    
  /** if(timeCounter == 250){
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
  }
  else if(timeCounter == 500){
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    }**/
    timeCounter = 0;
    break;
  }
   if(timeCounter % 10 ==0){
     P1OUT ^= LED_RED; //toggle red
   }
  
}


void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  advance_250th();
} 
