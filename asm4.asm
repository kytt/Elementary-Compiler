segment .bss
reg0	resb	8
reg1	resb	8
reg2	resb	8
reg3	resb	8
reg4	resb	8
reg5	resb	8
reg6	resb	8
reg7	resb	8
reg8	resb	8
reg9	resb	8
reg10	resb	8
reg11	resb	8
reg12	resb	8
reg13	resb	8
reg14	resb	8
reg15	resb	8
reg16	resb	8
reg17	resb	8
reg18	resb	8
reg19	resb	8
reg20	resb	8
reg21	resb	8
reg22	resb	8
reg23	resb	8
reg24	resb	8
reg25	resb	8
decstr	resb	10
ct1	resd	1

section .text

global _start

_start:
	mov	eax,100
	neg	eax
	call	 _printHex
	mov	eax,1
	int	0x80
_printHex:
	pushad
	mov	dword[ct1],0
	mov	edi,decstr
	add	edi,9
	xor	edx,edx
	push	'0'
	push	'x'

whileNotZeroH:
	mov	ebx,16
	div	ebx
	cmp	edx,9
	jg	toAscii
	add	edx,'0'
	jmp	putStr
toAscii:
	add	edx,55
putStr:
	mov	byte[edi],dl
	dec	edi
	inc	dword[ct1]
	xor	edx,edx
	cmp	eax,0
	jne	whileNotZeroH

	pop	edx
	mov	byte[edi],dl
	dec	edi
	inc	dword[ct1]
	xor	edx,edx

	pop	edx
	mov	byte[edi],dl
	dec	edi
	inc	dword[ct1]
	xor	edx,edx

	inc	edi
	mov	ecx, edi
	mov	edx,[ct1]
	mov	eax, 4
	mov	ebx, 1
	int	0x80

	popad
	ret
 section .data
