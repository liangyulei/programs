/*
Filename: getTableIndex.s
Author : Zhi Jia Teoh
User id : cs30xjk
Date : 22 Feb 2017
Description : This subroutine returns the index in hashtable
*/
.global getTableIndex
.section ".text"

/*
Function name : int getTableIndex(char const *, size_t);
Return Value : index in hashtable
Description : This function will calculate the hash key with
		hash() function, and modulo the return value
		with tableSize, and returns the value
Registers used: %i0 = ucSorted
		%i1 = tableSize
		%o0 = return value
		%01 = for converting to positive
*/

getTableIndex:
	save %sp,-96,%sp	!save window

	mov %i0,%o0		!mov param to %o0
	call hash		!call hash func
	nop			!%o0 = hash key

	mov %i1,%o1		!%o1 = tableSize
	call .rem		!%o0 = hashkey mod tablesize
	nop

	cmp %o0,%g0		!check if negative
	bge return
	nop

	mov -1,%o1		!convert positive to negative
	call .mul
	nop

return:
	mov %o0,%i0		!return value
	ret			!ret and restore
	restore

		

