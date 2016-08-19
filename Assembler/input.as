; Name: Yvgeny Konrad id: 312737620

.entry STR
.entry LOOP
.entry LENGTH
.extern L3
.extern W
.entry START
.extern K
MAINT:	mov2	W,r7
		cmp1	r0,#-5
START:	add2	#7,LENGTH
		sub1	$$,r2
		not1	r3
		clr1	r5
LOOP:	lea2	STR,r6
		inc2	r5
		dec1	W
		jmp1	L3
		bne1	LOOP
		red1	r4
		prn1	#30
		jsr1	START
		rts1
		stop1
		.data	7,-20,3
LENGTH:	.data	4,250,-9
STR:	.string	"Hello World!"