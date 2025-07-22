#include <msp430.h>
#include "led.h"
#include "switches.h"

void __interrupt_vec(WDT_VECTOR) WDT(){
  static int blinkCount = 0;
  const int blinkLimit = 25;  // 25 interrupts = ~1 sec if using default timer freq

  blinkCount++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;

    if (switch_state_down) {
      // S1 is pressed → toggle green LED blink state
      green_blink_state ^= 1;
      red_blink_state = 0;
    } else {
      // S1 is released → toggle red LED blink state
      red_blink_state ^= 1;
      green_blink_state = 0;
    }

    leds_changed = 1; // signal that LED should be updated
    led_update();
  }
}
