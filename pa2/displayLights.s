/*
Filename : displayLights.s
Author : Zhi Jia Teoh
User ID : cs30xjk
Date : Feb 8 2017
Description : This routine displays which bits are set with '*'
	and '-'
Sources of Help : Handout and Piazza
*/

/*
Function name : displayLights()
Prototype : void displayLights( const unsigned int lightBank[] );
Description : For each bit that is set, print *, otherwise
print '-'
Parameters : lightBank[]
Registers:
	%i0 holds lightBank address
	%l0 holds lightBank[0]
	$l1 holds lightBank[1]
	%l2 = bit tester/mask
	%l3 = resultant for and op
	%l4 = character counter
	%l5 = outerLoop counter
*/

.global displayLights
.section ".text"
STAR = '*'
DASH = '-'
SPACE = ' '
NEWLINE = '\n'
displayLights:
	save %sp,-96,%sp

	ld [%i0],%l0	!%l0 = lightBank[0]
	ld [%i0+4],%l1	!%l1 = lightBank[1]
	mov 1,%l5	!counter for outerLoop

	cmp %l5,2	!logic test
	bge end

outerLoop:
	clr %l4		!%l4 = for priting ' ' after 
			!every 4 characters
	set 0x80000000,%l2	!to test each bit
	
	cmp %l2,%g0	!logic test
	be noSpace_endLoop
	loop:
		and %l0,%l2,%l3	!test bit by bit
		cmp %l3,%g0	
		bne printStar	!if bit set, print *
		nop
		mov DASH,%o0	!else print -
		call printChar
		nop
		ba afterPrint
		nop

	printStar:
		mov STAR,%o0	!print *
		call printChar
		nop
	
	afterPrint:
		inc %l4		!inc %l4 and check if
		mov %l4,%o0	!divisible by 4
		mov 4,%o1
		call .rem
		nop
		cmp %o0,%g0
		bne noSpace_endLoop	!print space if %l4 mod 4 = 0
		set SPACE,%o0
		call printChar
		nop

	noSpace_endLoop:	
		srl %l2,1,%l2	!shift bit tester
		cmp %l2,%g0	!if all tested, end loop
		bne loop
		nop

		mov %l1,%l0	!replace %l0 by %l1 to
		inc %l5		!repeat for lightBanks[1]
		cmp %l5,2	!outerLoop repeater
		ble outerLoop
		nop
		set NEWLINE,%o0	!print newline when done
		call printChar
		nop
	end:
		ret
		restore
