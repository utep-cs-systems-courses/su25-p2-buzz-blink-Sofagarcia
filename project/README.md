This project demonstrates state-based behavior using the MSP430 controller.
It incorporates button input, LED control, and buzzer sounds to transition between different states.

Features:
-LED blinking with pattern changes
-buzzer with pitch chnages
-WDT interrupts
-uses buttons to switch cases

How it works:
1. The MSP430 initializes the LEDs, buzzer, buttons, and timer.
2. It starts in State 0.
3. Pressing each button advances to the next state:
    - State 0: LEDs off, buzzer silent.
    - State 1: LEDs blink, buzzer plays a tone.
    - State 2: Alternate LED blink, different tone.
    - State 3: Solid LED, buzzer off.
4. State transitions loop back to 0 after the last state.
