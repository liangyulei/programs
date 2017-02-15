/*
Filename: toggle.s
Author : Zhi Jia Teoh
User id :cs30xjk
Date : 14 Feb 2017
Description : Toggle each lightBank element according to pattern
Sources of help : Piazza and TA's
*/

.global toggle
.section ".text"

/*
Function name : toggle()
Function prototype : void toggle(unsigned int lightBank[],
		     const unsigned int pattern0,
		     const unsigned int pattern1);
Description: Toggles each bit in each lightBank element according
	     to the pattern bits
Parameters: lightBank[] = lightBank elements to be toggled
	    pattern0 = pattern for lightBank[0]
	    pattern1 = pattern for lightBank[1]
Registers used:
%i0 = lightBank[]
%i1 = pattern1
%i2 = pattern2
%l0 = store lightBank[0]
%l1 = store lightBank[1]
%l2 = pattern0 for xor
%l3 = pattern1 for xor
*/

toggle:
	save %sp,-96,%sp

	ld [%i0],%l0	!lightBank[0] = %l0
	ld [%i0+4],%l1	!lightBank[1] = %l1

	mov %i1,%l2	!pattern0 = %l2
	mov %i2,%l3	!pattern1 = %l3

	xor %l0,%l2,%l0	!toggle the bits
	xor %l1,%l3,%l1

	st %l0,[%i0]	!store to return
	st %l1,[%i0+4]

	ret		!return and restore
	restore
