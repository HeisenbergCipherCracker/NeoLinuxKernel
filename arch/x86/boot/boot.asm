; Bootloader code
[bits 16]
[org 0x7C00]

start:
    ; Bootloader code here
    jmp $

times 510-($-$$) db 0
dw 0xAA55
