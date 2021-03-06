.global shift
.section ".text"

shift:
	save %sp,-96,%sp
	
	ld [%i0],%l0	!%l0 = lightBank[0]
	ld [%i0+4],%l1	!%l1 = lightBank[1]
	
	set 0x80000000,%l2
	andcc %i1,%l2,%l2	!check MSB of shiftCnt
	bz positiveCount
	nop
	
	mov %i1,%l2		!get shiftCnt arg
	nop
	neg %l2			!2's complement
	and %l2,0x3F,%l2	!%l2 = counter value
	

	cmp %l2,%g0		!logic test to jump
	be endRightShiftLoop	!over loop
	nop

rightShiftLoop:
	set 0x00000001,%l3
	and %l0,%l3,%l3	!%l3 => LSB of lightBank[0]

	srl %l0,1,%l0	!shift both banks by 1
	srl %l1,1,%l1	

	cmp %l3,%g0	!check if any "jumping bit"
	be noShift
	nop
	set 0x80000000,%l3	!jumping bit present
	or %l1,%l3,%l1

	noShift:	!jumping bring absent
		dec %l2	!logic test to repeat loop
		cmp %l2,%g0
		bne rightShiftLoop
		nop
	endRightShiftLoop:	!loop ends
		ba end
		nop
	
positiveCount:
	mov %i1,%l2	
	nop
	and %l2,0x3F,%l2	!%l2 = counter value

	cmp %l2,%g0	!logic test to jump over loop
	be end
	nop

leftShiftLoop:
	set 0x80000000,%l3
	and %l1,%l3,%l3	!%l3 = MSB of lightBank[0]

	sll %l0,1,%l0	!shift both banks by 1
	sll %l1,1,%l1

	cmp %l3,%g0	!check if any "jumping" bit
	be _noShift
	nop
	set 0x00000001,%l3	!jumping bit present
	or %l0,%l3,%l0

	_noShift:	!jumping bit absent
		dec %l2
		cmp %l2,%g0	!logic test to repeat loop
		bne leftShiftLoop
		nop
		ba end	!loop ends
		nop
end:
	st %l0,[%i0]	!store back value to array
	st %l1,[%i0+4]
	ret	!return and restore
	restore
