	.arch msp430g2553
	.p2align 1, 0

	.extern redState

	.global test
	
	.text
test:
	call #redState
	pop R0
