/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
section .text
	global load_tss
	global get_eip

load_tss:
	mov ax, 0x2B
	ltr ax
	ret

get_eip:
	push eax
	jmp eax
	