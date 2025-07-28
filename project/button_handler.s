	.global __interrupt_vec_10
	.text

__interrupt_vec_10:
	bic.b   #0x08, &P2IFG     ; Clear P2.3 flag
	mov.w   #0, &current_state ; Reset state
	reti
