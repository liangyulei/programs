/*
Filename : set.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Date : Feb 8 2017
Description : This routine sets the lightBank array based on the patterns
Sources of Help : Piazza and Handout
*/


.global set
.section ".text"

/*
Function name : set()
Function prototype :
void set( unsigned int lightBank[], const unsigned int pattern0,
const unsigned int pattern1 )
Description : set lightBank elements based on patterns
Parameters :	lightBank => elements to set
		pattern0 => for first element
		pattern1 => for second element
Registers:
	%i0 = parameter for lightBank
	%l0 = holds lightBank[0]
	%l1 = holds lightBank[1]
	%i1 = holds pattern0
	%i2 = holds pattern1
*/

set:
	save %sp,-96,%sp
	
	ld [%i0],%l0	!save lightBank[0] to %l0
	ld [%i0+4],%l1 	!save lightBank[1] to %l1
	
	or %l0,%i1,%l0	!change patterns
	or %l1,%i2,%l1

	st %l0,[%i0]	!store back to array address
	st %l1,[%i0+4]

	ret
	restore
