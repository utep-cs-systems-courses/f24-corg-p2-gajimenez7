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
	;; moving count2 to register 4
	mov.w &count2, R4

	;; check if count2 is less than 3
	cmp.w #3, R4
	jl noSuprises_1

	;; if count 2 >= 3, go to second part of song
	call #noSuprises_2
	pop R0
	
noSuprises_1:
	mov.w &count, R5
	cmp.w #100, R5 		;check if count is less than 100
	jl check2_1

	call #redState
	call #noteA
call2_1:
	cmp.w #200, R5
	jl check3_1

	call #greenState
	call #noteB
call3_1:
	cmp.w #300, R5
	jl check4_1

	call #bothState
	call #noteC
call4_1:
	cmp.w #400, R5
	jl end_part1

	call #offState
	mov.w #0, &count
	add.w #1, &count2
	call #noteB
end_part1:
	pop R0
	
noSuprises_2:
	mov.w &count, R5
	cmp.w #100, R5
	jl check2_2

	call #greenState
	call #noteD
call2_2:
	cmp.w #200, R5
	jl check3_2

	call #redState
	call #noteE
call3_2:
	cmp.w #300, R5
	jl check4_2

	call #bothState
	call #noteC
call4_2:
	cmp.w #400, R5
	jl end_part2

	call #offState
	mov.w #0, &count
	add.w #1, &count2
	call #noteF
end_part2:
	pop R0
