	.data
count:	.word 0
count2:	 .word 0

	.arch msp430g2553
	.p2align 1,0
	.text

	.global noSuprises
	.global count
	.global count2

noSuprises:
	mov.w &count2, R4
