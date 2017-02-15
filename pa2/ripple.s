/*
Filename : ripple.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Date : 5/6/2014
Description : This routine creates a ripple effect on the lightbanks
	      and print each subsequent rotation
Sources of help : TA's and Piazza
*/

.global ripple
.section ".text"

/*
Function Name: ripple()
Function Prototype: void ripple (unsigned int lightBank[],const int rippleCnt);
Description: Set the array by rotating the ripplecnt, but call
	     displayLights after every bit rotated to create a ripple
	     effect
Parameters: lightBank[] = lightBanks to be used
	    rippleCnt   = the counter for ripple
Registers used:
%l0 = lightBank[0]
%l1 = lightBank[1]
%l2 = rippleCnt / loop counter
%l3 = used for bitwise operations
%g0 = for 0 digit comparison
*/

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
