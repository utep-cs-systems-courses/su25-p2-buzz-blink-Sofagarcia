#include "libTimer.h"
#include "led.h"

int main(void){
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterrupts();

  or_sr(0x18);
}


char ledState = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  switch(ledState){
  case 0: P1OUT |= LED_GREEN; ledState =1; break;
  case 1: P1OUT &= ~LED_GREEN; ledState = 2; break;
  case 2: ledState = 0;
  }
}
