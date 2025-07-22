//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int greenBlinkLimit = 4; // green duty cycle
int redBlinkLimit = 7; //red duty cycle
int greenCount = 0;
int redCount = 0;
int secondCount = 0;
  
int main(void) {
  P1DIR |= LEDS; //set pins as output
  P1OUT &= ~LEDS; //turn off all leds
 

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
//int blinkLimit = 5;  // duty cycle = 1/blinkLimit
//int blinkCount = 0;  // cycles 0...blinkLimit-1
//int secondCount = 0; // state var representing repeating ti
void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  //green pwm
  greenCount++;
  if(greenCount >= greenBlinkLimit){
    greenCount = 0;
    P1OUT |= LED_GREEN;
  }else{
    P1OUT &= ~LED_GREEN;
  }
  //red pwn
  redCount++;
  if(redCount >= redBlinkLimit){
    redCount = 0;
    P1OUT |= LED_RED;
  }else{
    P1OUT &= ~LED_RED;
  }
    
  
  // handle blinking 
  /** blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  **/
  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;

    //modify brightness (blink limits) in a loop from a dim to bright
    greenBlinkLimit++;	     // reduce duty cycle
    if(greenBlinkLimit > 7) greenBlinkLimit = 1;

    //red
    redBlinkLimit--;
    if(redBlinkLimit < 1) redBlinkLimit = 7;
  }
} 

