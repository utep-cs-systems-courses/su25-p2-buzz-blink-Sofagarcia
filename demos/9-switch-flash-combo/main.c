#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

void switch_init() {
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
}

void wdt_init() {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
}

void main(void) 
{  
  switch_init();
  led_init();
  wdt_init();
    
  or_sr(0x18);  // CPU off, GIE on
} 

static int buttonDown;
static int blinkMode = 0; //0=slow 1=fats 2=alty
static int blinkCounter = 0;
static int ledOn = 0;

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

  if (p1val & SW1) {		/* button up */
    P1OUT &= ~LED_GREEN;
    buttonDown = 0;
  } else {			/* button down */
    P1OUT |= LED_GREEN;
    buttonDown = 1;

    //so each button press moves to the next blink pattern
    blinkMode = (blinkMode + 1) % 3; //tis cycles through 0-1-2-0
    blinkCounter = 0;                //resets counter when changing mode
    ledOn = 0;
    P1OUT &= ~LEDS;                  //clears leds when mode changes
  }
}


/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){
  blinkCounter++;

  switch (blinkMode) {
  case 0: // Slow blink (RED)
    if (blinkCounter >= 75) { // ~3 blinks/sec
      blinkCounter = 0;
      ledOn ^= 1;
      if (ledOn)
        P1OUT |= LED_RED;
      else
        P1OUT &= ~LED_RED;
    }
    P1OUT &= ~LED_GREEN;
    break;

  case 1: // Fast blink (RED)
    if (blinkCounter >= 25) { // ~10 blinks/sec
      blinkCounter = 0;
      ledOn ^= 1;
      if (ledOn)
        P1OUT |= LED_RED;
      else
        P1OUT &= ~LED_RED;
    }
    P1OUT &= ~LED_GREEN;
    break;

  case 2: // Alternate RED ↔ GREEN
    if (blinkCounter >= 50) {
      blinkCounter = 0;
      ledOn ^= 1;
      if (ledOn) {
        P1OUT |= LED_RED;
        P1OUT &= ~LED_GREEN;
      } else {
        P1OUT |= LED_GREEN;
        P1OUT &= ~LED_RED;
      }
    }
    break;
  }
}

