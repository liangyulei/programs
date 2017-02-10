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
	

	cmp %l2,%g0
	be endRightShiftLoop
	nop

rightShiftLoop:
	set 0x00000001,%l3
	and %l0,%l3,%l3	!%l3 => LSB of lightBank[0]

	srl %l0,1,%l0
	srl %l1,1,%l1

	cmp %l3,%g0
	be noShift
	nop
	set 0x80000000,%l3
	or %l1,%l3,%l1

	noShift:
		dec %l2
		cmp %l2,%g0
		bne rightShiftLoop
		nop
	endRightShiftLoop:	
		ba end
		nop
	
positiveCount:
	mov %i1,%l2
	nop
	and %l2,0x3F,%l2	!%l2 = counter value

	cmp %l2,%g0
	be end
	nop

leftShiftLoop:
	set 0x80000000,%l3
	and %l1,%l3,%l3	!%l3 = MSB of lightBank[0]

	sll %l0,1,%l0
	sll %l1,1,%l1

	cmp %l3,%g0
	be _noShift
	nop
	set 0x00000001,%l3
	or %l0,%l3,%l0

	_noShift:
		dec %l2
		cmp %l2,%g0
		bne leftShiftLoop
		nop
		ba end
		nop
clear:
	and %l0,0,%l0
	and %l1,0,%l1
end:
	st %l0,[%i0]
	st %l1,[%i0+4]
	ret
	restore
