/*
Filename : shift.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Date : Feb 8 2017
Description : This routine shifts each bit L/R according to the counter
Sources of help : Handout and Piazza
*/

.global shift
.section ".text"
/*
Function Name : shift()
Prototype : void shift( unsigned int lightBank[], const int shiftCnt );
Description : Shift each bit left or right according to counter
Parameters : lightBank[] and shiftCnt
Registers:
	%l0 = hold lightBank[0]
	%l1 = hold lightBank[1]
	%l2 = counter value / temporary value for andcc op
	%l3 = temporary value for "jumping" bits
	      from one lightBank element to other

*/

shift:
	save %sp,-96,%sp
	
	ld [%i0],%l0	!%l0 = lightBank[0]
	ld [%i0+4],%l1	!%l1 = lightBank[1]
	
	set 0x80000000,%l2
	andcc %i1,%l2,%l2	!check MSB of shiftCnt
	bz positiveCount
	nop
	
	mov %i1,%l2		!get shiftCnt arg
	cmp %l2,-64		!if counter <= -64, set
	ble clear		!both lightBank elements to 0
	nop
	neg %l2			!2's complement
	
	and %l2,0x3F,%l2	!%l2 = counter value
	cmp %l2,%g0	!logic test
	be endRightShiftLoop
	nop

rightShiftLoop:
	set 0x00000001,%l3
	and %l0,%l3,%l3	!%l3 => LSB of lightBank[0]

	srl %l0,1,%l0	!shift both lightBank elements by 1
	srl %l1,1,%l1

	cmp %l3,%g0	!check if any jumping bits
	be noShift
	nop
	set 0x80000000,%l3
	or %l1,%l3,%l1	!place the jumping bit

	noShift:
		dec %l2		!dec counter and repeat loop
		cmp %l2,%g0
		bne rightShiftLoop
		nop
	endRightShiftLoop:	
		ba end
		nop
	
positiveCount:
	mov %i1,%l2	!%l2 = counter
	cmp %l2,64	!if counter >= 64,
	bge clear	!set both lightBank elements to 0
	nop

	and %l2,0x3F,%l2	!%l2 = counter value
	cmp %l2,%g0	!logic test
	be end
	nop

leftShiftLoop:
	set 0x80000000,%l3	
	and %l1,%l3,%l3	!%l3 = MSB of lightBank[0]

	sll %l0,1,%l0	!shift both lightBank elements by 1
	sll %l1,1,%l1

	cmp %l3,%g0	!check if any jumping bits
	be _noShift
	nop
	set 0x00000001,%l3
	or %l0,%l3,%l0	!set jumping bits

	_noShift:
		dec %l2	!dec counter and repeat loop
		cmp %l2,%g0
		bne leftShiftLoop
		nop
		ba end
		nop
clear:
	and %l0,0,%l0	!clearing both lightBank elements
	and %l1,0,%l1
end:
	st %l0,[%i0]	!store back values to array address
	st %l1,[%i0+4]	!and return
	ret
	restore
