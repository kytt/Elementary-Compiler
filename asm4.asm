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
	mov	eax,5
	mov	[reg2],eax
	mov	eax,[reg1]
	push	eax
	mov	eax,[reg2]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label1

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label2:
	push	ecx
	mov	eax,[reg1]
	push	eax
	mov	eax,[reg2]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label3

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label4:
	push	ecx
	mov	ecx,str1
	mov	edx,1
	call	_printString
	pop	ecx
	loop	label4
label3:
	mov	eax,[reg1]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg1],eax
	mov	ecx,str2
	mov	edx,0
	call	_printString
	call	 _printLn
	pop	ecx
	loop	label2
label1:
	mov	eax,0
	mov	[reg1],eax
	mov	eax,5
	mov	[reg2],eax
	mov	eax,5
	mov	[reg3],eax
	mov	eax,[reg1]
	push	eax
	mov	eax,[reg2]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label5

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label6:
	push	ecx
	mov	eax,[reg3]
	push	eax
	mov	eax,[reg2]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jg	label7

	sub	ebx,eax
	mov	ecx,ebx
	inc	ecx
label8:
	push	ecx
	mov	ecx,str3
	mov	edx,1
	call	_printString
	pop	ecx
	loop	label8
label7:
	mov	eax,[reg3]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	sub	eax,ebx
	mov	[reg3],eax
	mov	ecx,str4
	mov	edx,0
	call	_printString
	call	 _printLn
	pop	ecx
	loop	label6
label5:
	mov	ecx,str5
	mov	edx,0
	call	_printString
	call	 _printLn
	mov	ecx,str6
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str7
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str8
	mov	edx,18
	call	_printString
	call	 _printLn
	mov	ecx,str9
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str10
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str11
	mov	edx,18
	call	_printString
	call	 _printLn
	mov	ecx,str12
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str13
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	eax,0
	mov	[reg6],eax
	mov	eax,1
	mov	[reg7],eax
	mov	eax,2
	mov	[reg8],eax
	mov	eax,3
	mov	[reg9],eax
	mov	eax,4
	mov	[reg4],eax
	mov	eax,5
	mov	[reg5],eax
	mov	eax,6
	mov	[reg1],eax
	mov	eax,7
	mov	[reg1],eax
	mov	eax,[reg6]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	add	eax,ebx
	mov	[reg6],eax
	mov	eax,[reg6]
	push	eax
	mov	eax,[reg7]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jne	label9

	mov	eax,[reg9]
	push	eax
	mov	eax,1
	mov	ebx,eax
	pop	eax
	sub	eax,ebx
	mov	[reg9],eax
	mov	eax,[reg8]
	push	eax
	mov	eax,[reg9]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jne	label10

	mov	eax,[reg4]
	push	eax
	mov	eax,[reg5]
	mov	ebx,eax
	pop	eax
	cmp	eax,ebx
	jne	label11

	jmp	label12

label11:
	mov	ecx,str14
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str15
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str16
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str17
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str18
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str19
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str20
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str21
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str22
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str23
	mov	edx,60
	call	_printString
	call	 _printLn

label12:

label10:

label9:
	mov	eax,1
	int	0x80
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
str1	db	"*"
str2	db	""
str3	db	"*"
str4	db	""
str5	db	""
str6	db	"*****  ******  ******"
str7	db	" ***  *******  ******"
str8	db	" ***  ***      ***"
str9	db	" ***  ***      ******"
str10	db	" ***  ***      ******"
str11	db	" ***  ***      ***"
str12	db	" ***  *******  ******"
str13	db	"*****  ******  ******"
str14	db	"░▄▀▄▀▀▀▀▄▀▄░░░░░░░░░"
str15	db	"░█░░░░░░░░▀▄░░░░░░▄░"
str16	db	"█░░▀░░▀░░░░░▀▄▄░░█░█"
str17	db	"█░▄░█▀░▄░░░░░░░▀▀░░█"
str18	db	"█░░▀▀▀▀░░░░░░░░░░░░█"
str19	db	"█░░░░░░░░░░░░░░░░░░█"
str20	db	"█░░░░░░░░░░░░░░░░░░█"
str21	db	"░█░░▄▄░░▄▄▄▄░░▄▄░░█░"
str22	db	"░█░▄▀█░▄▀░░█░▄▀█░▄▀░"
str23	db	"░░▀░░░▀░░░░░▀░░░▀░░░"
nl	db	10
