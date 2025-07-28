#ifndef LEDS_H
#define LEDS_H

void led_init();
void set_led_blink(unsigned int rate);
void set_led_brightness(unsigned int level);
void leds_off();

void red_on();
void red_off();
void green_on();
void green_off();

#endif
