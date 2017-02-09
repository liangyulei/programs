/*
Filename : printChar.s
Author : Zhi Jia Teoh
Date : Feb 8 2017
UserID : cs30xjk
Description : prints char
*/

.global printChar
.section ".data"

/*
Function name : printChar(char ) 
Description : Prints according to the format from arg value
Return : void
*/

fmt:
.asciz "%c"

.section ".text"
printChar:
	save %sp,-96,%sp
	set fmt,%o0
	mov %i0,%o1
	call printf,2
	nop

	ret
	restore

