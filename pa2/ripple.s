.global ripple
.section ".text"

ripple:
	save %sp,-96,%sp

	ld [%i0],%l0	!%l0 = lightBank[0]
	ld [%i0+4],%l1	!%l1 = lightBank[1]

	mov %i1,%l2	!%l2 = rippleCnt

	set 0x80000000,%l3	!check if rippleCnt + or -
	and %l2,%l3,%l3

	cmp %l3,%g0	!check if -bit set
	be positive
	nop
	
	cmp %l2,%g0	!logic test to skip loop body
	be endNegLoop
	nop
	
	loopNeg:	!negative cnt loop
	
	mov %i0,%o0	!rotate a single bit right
	mov -1,%o1
	call rotate	
	nop

	mov %i0,%o0	!show ripple bits
	call displayLights
	nop
	
	inc %l2		!inc counter (neg counter)
	cmp %l2,%g0	!logic test to repeat loop
	bne loopNeg
	nop
	
	endNegLoop:

	ba endLoop	!loop ends
	nop

positive:

	cmp %l2,%g0
	be endLoop
	nop
	
	loopPos:

	mov %i0,%o0	!rotate a single bit left
	mov 1,%o1
	call rotate
	nop

	mov %i0,%o0	!show ripple bits
	call displayLights
	nop

	dec %l2		!dec counter (pos counter)
	cmp %l2,%g0	!logic test to repeat loop
	bne loopPos
	nop

endLoop:
	ret		!return and restore
	restore
