/*
Filename : charCompare.s
Author : Zhi Jia Teoh
UserID : cs30xjk
Date : 22 Feb 2017
Description : Leaf subroutine that compares two characters
		and returns the appropriate value
*/

.global charCompare
.section ".text"

/*
Function prototyope : int charCompare(void const *, void const *);
Return value : 0 if equal, -1 if arg1 smaller, 1 if arg1 bigger
Registers used : %o0 = arg1 and ret value
		 %o1 = arg2
*/

charCompare:
	ldub [%o0],%o0		!load both chars
	ldub [%o1],%o1

	cmp %o0,%o1		!cmp the two chars
	bl less			!branch if %l0<%l1
	nop

	cmp %o0,%o1		!cmp two chars
	bg greater		!branch if %l0>%l1
	nop

	mov 0,%o0		!set return value to 0
	ba return
	nop

less:	
	mov -1,%o0		!set return value to -1
	ba return
	nop

greater:			!set return value to 1
	mov 1,%o0

return:
	retl			!return
	nop
