/*
Filename : hash.s
Author : Zhi Jia Teoh
UserID : cs30xjk
Date : 22 Feb 2017
Description : This function returns the hash value of a string
*/

.global hash
.section ".text"

/*
Function name : int hash(char const *);
Return value : hash key
Description : This function takes the string param and
		"hashes" it according to Java's String.hashCode()
		and returns the value
Registers used : %i0 = str
		 %l0 = hash_start_val
		 %l1 = hash_prime
		 %o0 = strlen/.mul param
		 %o1 = .mul param
		 %l2 = strlen
		 %l3 = counter
		 %g0 = comparison for 0
*/
hash:
	save %sp,-96,%sp	!save window

	set HashStartVal,%l0	!set %l0 to HASH_START_VAL 
	set HashPrime,%l1	!set %l1 to HASH_PRIME

	ld [%l0],%l0		!%l0 = HASH_START_VAL value
	ld [%l1],%l1		!%l1 = HASH_PRIME value

	mov %i0,%o0		!call strlen(str)
	call strlen
	nop

	mov %o0,%l2		!%l2 = strLen
	
	clr %l3			!set counter to 0
	cmp %l3,%l2		!if i>=strLen
	bge return
	nop

loop:
	mov %l0,%o0		!%o0 = hash
	mov %l1,%o1		!%o1 = hash_prime 
	call .mul		!%o0 = hash*hash_prime
	nop
	
	ldub [%i0+%l3],%l0	!%l0 = str[i]
	
	add %l0,%o0,%l0		!%l0 = hash = hash*hash_prime+str[i]
	
	inc %l3			!inc counter
	cmp %l3,%l2		!if i<strLen
	bl loop
	nop

return:
	mov %l0,%i0
	ret			!return and restore
	restore
	


