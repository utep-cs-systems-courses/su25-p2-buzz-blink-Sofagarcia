#include <msp430.h>
#include "timer.h"

void configureClocks() {
    BCSCTL1 = CALBC1_1MHZ;    // Set range
    DCOCTL = CALDCO_1MHZ;     // Set DCO step + modulation
}

void enableWDTInterrupts() {
    WDTCTL = WDT_MDLY_8;              // Watchdog Timer interval: ~8ms
    IE1 |= WDTIE;                     // Enable WDT interrupt
}
