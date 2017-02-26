/*
Filename : isInBounds.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Description : SPARC assembly routine to check if number is
	      in bounds within a range
Date : January 25 2017
Help Sources : Piazza
*/

.global isInBounds
.section ".text"

/*
Function Name : isInBounds()
Function Prototype : long isInBounds( long min, long dist, long num );
Description : Checks whether the num is in between (inclusive) min
	      and min+dist
Parameters : arg 1 -- min , arg 2 -- dist, arg 3 -- num
Side Effects : None
Error Conditions : Negative dist
Return value : 1 -- in range, 0 -- not in rage, -1 -- negative dist
Registers used:
%i0 -- param for min and also return result
$i1 -- param for dist
%i2 -- param for num and for cmp operations
%o0 -- store min and first operation for addcc/cmp operations
%l0 -- store min+dist and for cmp operations
*/

isInBounds:
	save %sp,-96,%sp

	mov %i0,%o0	!min
	mov %i1,%o1	!dist
			!num in %i2

	cmp 0,%o1 	!check if dist is negative
	bg error 	!if 0>dist => dist is negative
	nop
	
	addcc %o0,%o1,%l0	!compute min+dist, sum in %l0
	bvs error	!overflow error
	nop

	cmp %o0,%i2	!check min>num
	bg false	!if min>num
	nop

	cmp %l0,%i2	!check min+dist<num
	bl false	!if min+dist<num
	nop

	mov 1,%i0	!num is in correct range
	ret
	restore

	false:		!num is not in between min and min+dist
		mov 0,%i0
		ret
		restore
	
	error:		!either overflow error OR dist is negative
		mov -1,%i0
		ret
		restore



