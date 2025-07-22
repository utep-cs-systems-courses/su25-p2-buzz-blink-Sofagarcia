//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

//SETUP
int main(void) {
  P1DIR |= LEDS; //set pins as outputs
  P1OUT &= ~LEDS; //turn off all leds


  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

//LED CONTROL

void greenControl(int on){
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}


//BLINK STATE MACHINE

//contorls brightness via softaware PWM
static int blinkLimit = 1;   //  1 to 7 controls brightness (1=brightness, 7=dimmest) 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1); //turn led on
  } else{
    greenControl(0); //turn led off
  }
}


//ONE SECOND EVENT STATE MACHINE

//increases blinklimit once oper second, to make th light appear dimmer gradually
void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;  // reduce duty cycle
  //reset after dimmest setting
  if (blinkLimit >= 7)  // but don't let duty cycle go below 1/7.
    blinkLimit = 1;
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond(); //trigger brightness change
  } }

//MASTER STATE MACHINE
void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate(); //handle pwm blink logic
  secondUpdate(); //handle 1-second timing logic
}


//WDT INTERRUPT HANDLER
void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 

