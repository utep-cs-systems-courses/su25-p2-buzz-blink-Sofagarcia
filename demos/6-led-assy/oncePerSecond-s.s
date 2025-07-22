    .global oncePerSecond
    .extern blinkLimit

oncePerSecond:
    ; increment blinkLimit
    mov &blinkLimit, r12     ; r12 = blinkLimit
    add #1, r12              ; r12 += 1

    ; if blinkLimit >= 8, reset to 0
    cmp #8, r12
    jl no_reset              ; if less than 8, skip reset
    mov #0, r12              ; else reset to 0

no_reset:
    mov r12, &blinkLimit     ; store new value
    ret
