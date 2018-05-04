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
	mov	eax,1
	mov	[reg1],eax
	mov	eax,2
	mov	[reg2],eax
	mov	eax,3
	mov	[reg3],eax
	mov	eax,4
	mov	[reg4],eax
	mov	eax,5
	mov	[reg5],eax
	mov	eax,6
	mov	[reg6],eax
	mov	eax,7
	mov	[reg7],eax
	mov	eax,8
	mov	[reg8],eax
	mov	eax,9
	mov	[reg9],eax
	mov	eax,10
	mov	[reg10],eax
	mov	eax,11
	mov	[reg11],eax
	mov	eax,12
	mov	[reg12],eax
	mov	eax,13
	mov	[reg13],eax
	mov	eax,14
	mov	[reg14],eax
	mov	eax,15
	mov	[reg15],eax
	mov	eax,16
	mov	[reg16],eax
	mov	eax,17
	mov	[reg17],eax
	mov	eax,18
	mov	[reg18],eax
	mov	eax,19
	mov	[reg19],eax
	mov	eax,20
	mov	[reg20],eax
	mov	eax,21
	mov	[reg21],eax
	mov	eax,22
	mov	[reg22],eax
	mov	eax,23
	mov	[reg23],eax
	mov	eax,24
	mov	[reg24],eax
	mov	eax,25
	mov	[reg25],eax
	mov	eax,[reg0]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg1]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg2]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg3]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg4]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg5]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg6]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg7]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg8]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg9]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg10]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg11]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg12]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg13]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg14]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg15]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg16]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg17]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg18]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg19]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg20]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg21]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg22]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg23]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg24]
	call	 _printDec
	call	 _printLn
	mov	eax,[reg25]
	call	 _printDec
	call	 _printLn
	mov	ecx,str1
	mov	edx,0
	call	_printString
	call	 _printLn
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
	mov	ecx,str2
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
	mov	ecx,str3
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
	mov	ecx,str4
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
	mov	ecx,str5
	mov	edx,0
	call	_printString
	call	 _printLn
	pop	ecx
	loop	label6
label5:
	mov	ecx,str6
	mov	edx,0
	call	_printString
	call	 _printLn
	mov	ecx,str7
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str8
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str9
	mov	edx,18
	call	_printString
	call	 _printLn
	mov	ecx,str10
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str11
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str12
	mov	edx,18
	call	_printString
	call	 _printLn
	mov	ecx,str13
	mov	edx,21
	call	_printString
	call	 _printLn
	mov	ecx,str14
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
	mov	[reg10],eax
	mov	eax,7
	mov	[reg11],eax
	mov	ecx,str15
	mov	edx,0
	call	_printString
	call	 _printLn
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
	mov	ecx,str24
	mov	edx,60
	call	_printString
	call	 _printLn
	mov	ecx,str25
	mov	edx,60
	call	_printString
	call	 _printLn

label12:

label10:

label9:
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
str1	db	""
str2	db	"*"
str3	db	""
str4	db	"*"
str5	db	""
str6	db	""
str7	db	"*****  ******  ******"
str8	db	" ***  *******  ******"
str9	db	" ***  ***      ***"
str10	db	" ***  ***      ******"
str11	db	" ***  ***      ******"
str12	db	" ***  ***      ***"
str13	db	" ***  *******  ******"
str14	db	"*****  ******  ******"
str15	db	""
str16	db	"░▄▀▄▀▀▀▀▄▀▄░░░░░░░░░"
str17	db	"░█░░░░░░░░▀▄░░░░░░▄░"
str18	db	"█░░▀░░▀░░░░░▀▄▄░░█░█"
str19	db	"█░▄░█▀░▄░░░░░░░▀▀░░█"
str20	db	"█░░▀▀▀▀░░░░░░░░░░░░█"
str21	db	"█░░░░░░░░░░░░░░░░░░█"
str22	db	"█░░░░░░░░░░░░░░░░░░█"
str23	db	"░█░░▄▄░░▄▄▄▄░░▄▄░░█░"
str24	db	"░█░▄▀█░▄▀░░█░▄▀█░▄▀░"
str25	db	"░░▀░░░▀░░░░░▀░░░▀░░░"
nl	db	10
