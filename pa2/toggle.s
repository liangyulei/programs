.global toggle
.section ".text"

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
