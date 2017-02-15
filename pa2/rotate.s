/*
Filename : rotate.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Date : 14 Feb 2017
Description : Rotate each lightBank element by the rotation count
Sources of help : Piazza and TA's
*/

.global rotate
.section ".text"

/*
Funtion name : rotate()
Function Prototyope : void rotate(unsigned int lightBank[]
		      , const int rotateCnt);
Description: Rotate each lightBank by the rotation count
Parameters: lightBank[] = lightBanks to be rotated
	    rotateCnt = rotation counter
Registers:
%i0 = lightBank[] parameter
%i1 = rotateCnt parameter
%l0 = store lightBank[0]
%l1 = store lightBank[1]
%l2 = store rotateCnt
%l3 = for getting MSB/LSB across
%l4 = rotate bit for MSB/LSB
%g0 = comparison for 0
*/

rotate:
	save %sp,-96,%sp
	
	ld [%i0],%l0	!%l0 = lightBank[0]
	ld [%i0+4],%l1	!%l1 = lightBank[1]
	
	set 0x80000000,%l2
	andcc %i1,%l2,%l2	!check MSB of rotateCnt
	bz positiveCount
	nop
	
	mov %i1,%l2		!get rotateCnt arg
	nop
	neg %l2			!2's complement
	and %l2,0x3F,%l2	!%l2 = counter value
	

	cmp %l2,%g0	!logic test to skip loop
	be endRightShiftLoop
	nop

rightShiftLoop:
	set 0x00000001,%l3
	and %l0,%l3,%l3	!%l3 => LSB of lightBank[0]
	set 0x00000001,%l4
	and %l1,%l4,%l4	!%l4 => LSB of lightBank[1]

	srl %l0,1,%l0	!shift both banks by 1
	srl %l1,1,%l1

	cmp %l4,%g0	!check if rotate value 0 or 1
	be noRotate
	nop
	set 0x80000000,%l4	!rotate value 1
	or %l4,%l0,%l0

	noRotate:	!rotate value 0

	cmp %l3,%g0	!check if any "jumping" bit
	be noShift
	nop
	set 0x80000000,%l3	!jumping bit present
	or %l1,%l3,%l1

	noShift:	!jumping bit absent
		dec %l2
		cmp %l2,%g0	!logic test to repeat loop
		bne rightShiftLoop
		nop
	endRightShiftLoop:	!end loop
		ba end
		nop
	
positiveCount:
	mov %i1,%l2
	nop
	and %l2,0x3F,%l2	!%l2 = counter value

	cmp %l2,%g0	!logic test to skip loop body
	be end
	nop

leftShiftLoop:
	set 0x80000000,%l3
	and %l1,%l3,%l3	!%l3 = MSB of lightBank[1]
	set 0x80000000,%l4 !%l4 = MSB of lightBank[0]
	and %l0,%l4,%l4	

	sll %l0,1,%l0	!shift both banks by 1
	sll %l1,1,%l1
	
	cmp %l4,%g0	!check if rotated value is 0
	be _noRotate	!or 1
	nop
	inc %l1		!rotate value 1

	_noRotate:	!rotate value 0

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
		ba end	!end loop
		nop
end:
	st %l0,[%i0]	!store back values to array
	st %l1,[%i0+4]
	ret	!return and restore
	restore
