#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT0		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

static int blink_state = 0; //0 = blink red, 1= blink green
static int led_on = 0; 
static int led_state = 0; //0=red, 1=green

void main(void) 
{  
  configureClocks(); //from libTimer
  enableWDTInterrupts(); //enable periodic interrupts

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

void
switch_interrupt_handler()
{
  char p1val = P1IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  //check for press
  if(!(p1val & SW1)){ //button is pressed (0=active low)
    blink_state ^= 1; //toggle state
    led_on = 0;       //reset led state
    P1OUT &= ~LEDS;   //turn off both leds immediately
    
    /* if(led_state){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    }else{
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
      }*/
  }
  
/* up=red, down=green
  if (p1val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  } */
}

void __interrupt_vec(WDT_VECTOR) WDT(){
  led_on ^= 1; // toggle LED state (on/off)

  if (blink_state == 0) {
    if (led_on)
      P1OUT |= LED_RED;
    else
      P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    if (led_on)
      P1OUT |= LED_GREEN;
    else
      P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
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
