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
	mov	ecx,str1
	mov	edx,20
	call	_printString
	mov	eax,2
	mov	[reg1],eax
	mov	eax,2
	mov	[reg4],eax
	mov	eax,0
	mov	[reg5],eax
	mov	eax,2
	push	eax
	mov	eax,97
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label1

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label2:
	push	ecx
	mov	eax,2
	push	eax
	mov	eax,[reg1]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label3

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label4:
	push	ecx
	mov	eax,[reg1]
	push	eax
	mov	eax,[reg4]
	xor	edx,edx
	mov	ebx,eax
	pop	eax
	idiv	ebx
	mov	eax,edx
	mov	[reg3],eax
	mov	eax,[reg3]
	push	eax
	mov	eax,0
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jne	label5

	mov	eax,[reg5]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg5],eax

label5:
	mov	eax,[reg4]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg4],eax
	pop	ecx
	dec	ecx
	jnz	label4
label3:
	mov	eax,[reg5]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jne	label6

	mov	eax,[reg1]
	call	 _printDec
	mov	ecx,str2
	mov	edx,1
	call	_printString

label6:
	mov	eax,0
	mov	[reg5],eax
	mov	eax,2
	mov	[reg4],eax
	mov	eax,[reg1]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg1],eax
	pop	ecx
	dec	ecx
	jnz	label2
label1:
	mov	ecx,str3
	mov	edx,0
	call	_printString
	call	 _printLn
	mov	eax,1
	int	0x80
_printDec:
	pushad
	mov	dword[ct1],0
	mov	edi,decstr
	add	edi,9
	xor	edx,edx

	push	0
	cmp	eax,0
	jge	whileNotZeroD
	pop	ebx
	push	'-'
	neg	eax
whileNotZeroD:
	mov	ebx,10
	div	ebx
	add	edx,'0'
	mov	byte[edi],dl
	dec	edi
	inc	dword[ct1]
	xor	edx,edx
	cmp	eax,0
	jne	whileNotZeroD
	pop	edx
	cmp	edx,0
	je	skip

	mov	byte[edi],dl
	dec	edi
	inc	dword[ct1]
	xor	edx,edx

skip:
	inc	edi
	mov	ecx, edi
	mov	edx,[ct1]
	mov	eax, 4
	mov	ebx, 1
	int	0x80

	popad
	ret
 _printString:
	push	eax
	push	ebx

	mov	eax,4
	mov	ebx,1
	int	0x80

	pop	ebx
	pop	eax
	ret
_printLn:
	push	ecx
	push	edx

	mov	ecx, nl
	mov	edx, 1
	call	_printString

	pop	edx
	pop	ecx
	ret
section .data
str1	db	"Prime Numbers are : "
str2	db	" "
str3	db	""
nl	db	10
