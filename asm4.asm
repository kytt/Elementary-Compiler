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
	mov	eax,[reg1]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg1],eax
	mov	eax,1
	int	0x80
section .data
