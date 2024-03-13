/*
*Neo Linux: A cutting-edge kernel for
*next-generation computing, released under the GPL 3.0 license. READ LICENSE file for more information
*/
	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 2
	.globl	_vga_entry                      ; -- Begin function vga_entry
	.p2align	2
_vga_entry:                             ; @vga_entry
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	strb	w0, [sp, #15]
	strb	w1, [sp, #14]
	strb	w2, [sp, #13]
	strh	wzr, [sp, #10]
	strb	wzr, [sp, #9]
	strb	wzr, [sp, #8]
	ldrb	w8, [sp, #13]
	strb	w8, [sp, #9]
	ldrb	w8, [sp, #9]
	lsl	w8, w8, #4
	strb	w8, [sp, #9]
	ldrb	w9, [sp, #14]
	ldrb	w8, [sp, #9]
	orr	w8, w8, w9
	strb	w8, [sp, #9]
	ldrb	w8, [sp, #9]
	strh	w8, [sp, #10]
	ldrh	w8, [sp, #10]
	lsl	w8, w8, #8
	strh	w8, [sp, #10]
	ldrb	w8, [sp, #15]
	strb	w8, [sp, #8]
	ldrb	w9, [sp, #8]
	ldrh	w8, [sp, #10]
	orr	w8, w8, w9
	strh	w8, [sp, #10]
	ldrh	w0, [sp, #10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_clear_vga_buffer               ; -- Begin function clear_vga_buffer
	.p2align	2
_clear_vga_buffer:                      ; @clear_vga_buffer
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	str	wzr, [sp]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp]
	subs	w8, w8, #2200
	cset	w8, hs
	tbnz	w8, #0, LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldrb	w1, [sp, #7]
	ldrb	w2, [sp, #6]
	mov	w0, #0
	bl	_vga_entry
	ldr	x8, [sp, #8]
	ldr	x8, [x8]
	ldr	w9, [sp]
                                        ; kill: def $x9 killed $w9
	strh	w0, [x8, x9, lsl  #1]
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp]
	add	w8, w8, #1
	str	w8, [sp]
	b	LBB1_1
LBB1_4:
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_init_vga                       ; -- Begin function init_vga
	.p2align	2
_init_vga:                              ; @init_vga
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	sturb	w0, [x29, #-1]
	sturb	w1, [x29, #-2]
	adrp	x0, _vga_buffer@GOTPAGE
	ldr	x0, [x0, _vga_buffer@GOTPAGEOFF]
	mov	x8, #32768
	movk	x8, #11, lsl #16
	str	x8, [x0]
	ldurb	w1, [x29, #-1]
	ldurb	w2, [x29, #-2]
	bl	_clear_vga_buffer
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_kernel_entry                   ; -- Begin function kernel_entry
	.p2align	2
_kernel_entry:                          ; @kernel_entry
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, _vga_buffer@GOTPAGE
	ldr	x8, [x8, _vga_buffer@GOTPAGEOFF]
	stur	x8, [x29, #-8]                  ; 8-byte Folded Spill
	mov	w0, #15
	str	w0, [sp, #16]                   ; 4-byte Folded Spill
	mov	w1, #0
	stur	w1, [x29, #-12]                 ; 4-byte Folded Spill
	bl	_init_vga
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	mov	w0, #72
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8]
	mov	w0, #101
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #2]
	mov	w0, #108
	str	w0, [sp, #12]                   ; 4-byte Folded Spill
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x9, [x29, #-8]                  ; 8-byte Folded Reload
	mov	x8, x0
	ldr	w0, [sp, #12]                   ; 4-byte Folded Reload
	ldr	x9, [x9]
	strh	w8, [x9, #4]
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #6]
	mov	w0, #111
	str	w0, [sp, #8]                    ; 4-byte Folded Spill
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #8]
	mov	w0, #32
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #10]
	mov	w0, #87
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x9, [x29, #-8]                  ; 8-byte Folded Reload
	mov	x8, x0
	ldr	w0, [sp, #8]                    ; 4-byte Folded Reload
	ldr	x9, [x9]
	strh	w8, [x9, #12]
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #14]
	mov	w0, #114
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x9, [x29, #-8]                  ; 8-byte Folded Reload
	mov	x8, x0
	ldr	w0, [sp, #12]                   ; 4-byte Folded Reload
	ldr	x9, [x9]
	strh	w8, [x9, #16]
	bl	_vga_entry
	ldr	w1, [sp, #16]                   ; 4-byte Folded Reload
	ldur	w2, [x29, #-12]                 ; 4-byte Folded Reload
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #18]
	mov	w0, #100
	bl	_vga_entry
	ldur	x8, [x29, #-8]                  ; 8-byte Folded Reload
	ldr	x8, [x8]
	strh	w0, [x8, #20]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.comm	_vga_buffer,8,3                 ; @vga_buffer
.subsections_via_symbols
