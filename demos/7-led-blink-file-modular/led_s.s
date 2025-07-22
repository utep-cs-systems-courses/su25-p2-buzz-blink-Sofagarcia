    .data
    .global red_on
    .global green_on
    .global led_changed
	.equ LEDS, 0x41
	
red_on:        .byte 0
green_on:      .byte 0
led_changed:   .byte 0

redVal:        .byte 0, 1          ; 0, LED_RED
greenVal:      .byte 0, 64         ; 0, LED_GREEN (0x40)

    .text
    .global led_init
    .global led_update
    .extern P1DIR
    .extern P1OUT

    .extern LEDS

led_init:
    ; Set P1DIR |= LEDS
    mov.b   &P1DIR, r12
    bis.b   &LEDS, r12
    mov.b   r12, &P1DIR

    ; Set led_changed = 1
    mov.b   #1, &led_changed

    ; Call led_update
    call    #led_update

    ret

led_update:
    mov.b   &led_changed, r12
    cmp.b   #0, r12
    jeq     done                  ; if led_changed == 0, skip update

    ; char ledFlags = redVal[red_on] | greenVal[green_on]
    mov.b   &red_on, r12
    mov.b   redVal(r12), r13      ; r13 = redVal[red_on]

    mov.b   &green_on, r14
    mov.b   greenVal(r14), r15    ; r15 = greenVal[green_on]

    bis.b   r15, r13              ; r13 = ledFlags = red | green

    ; P1OUT &= (0xff^LEDS) | ledFlags
    mov.b   &P1OUT, r12
    bic.b   &LEDS, r12            ; clear bits in LEDS mask
    bis.b   r13, r12              ; set bits from ledFlags
    mov.b   r12, &P1OUT

    ; led_changed = 0
    mov.b   #0, &led_changed

done:
    ret
