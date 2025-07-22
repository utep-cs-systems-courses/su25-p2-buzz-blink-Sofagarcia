#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char leds_changed = 0;
unsigned char green_led_state = 0;
unsigned char red_led_state = 0;


unsigned char red_blink_state = 0;
unsigned char green_blink_state = 0;
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if (leds_changed) {
    char ledFlags = 0; // no LEDs on by default

    if (switch_state_down) {
      if (green_blink_state)
        ledFlags |= LED_GREEN;
    } else {
      if (red_blink_state)
        ledFlags |= LED_RED;
    }

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;                 // set bits for on leds
    leds_changed = 0;
  }
  /*if (switch_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */

  /*ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;*/
}

