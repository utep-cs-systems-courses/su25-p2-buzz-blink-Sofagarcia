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



char setCount = 0;

void
oncePerSec()
{
  static char redState = 0;
  switch (redstate) {
  case 0:
    redState = 1; P1OUT |= LED_RED; break;
  case 1:
    redState = 0; P1OUT &= ~LED_RED; break;
  }
}

char ledState = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()
{
  secCount++;
  if(secCount == 250){
    secCount = 0;
    oncePerSec();
  }
  
  switch(ledState){
  case 0: P1OUT |= LED_GREEN; ledState =1; break;
  case 1: P1OUT &= ~LED_GREEN; ledState = 2; break;
  case 2: ledState = 0;
  }
}
