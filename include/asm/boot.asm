; boot.asm
BITS 16             ; 16-bit code
org 0x7c00          ; BIOS loads the boot sector at 0x7C00

start:
  mov ax, 0x07C0    ; Set up the segment registers
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov si, welcome_msg ; Print a welcome message
  call print_string

  ; Load the kernel
  mov ax, 0x1000    ; Load the kernel to 0x1000:0x0000
  mov es, ax
  mov bx, 0x0000
  mov ah, 0x02      ; BIOS function for disk read
  mov al, 1         ; Read one sector
  mov ch, 0         ; Cylinder number
  mov dh, 0         ; Head number
  mov dl, 0         ; Drive number
  int 0x13          ; BIOS disk interrupt
  jc disk_error     ; Jump if error

  ; Jump to the kernel
  jmp 0x1000:0x0000

disk_error:
  mov si, disk_error_msg
  call print_string

print_string:
  lodsb             ; Load next byte from SI into AL
  cmp al, 0         ; Check for null terminator
  je done
  mov ah, 0x0E      ; BIOS function for tty output
  mov bh, 0x00      ; Page number
  mov bl, 0x07      ; Text attribute (white on black)
  int 0x10          ; BIOS video interrupt
  jmp print_string  ; Continue printing
done:
  ret

welcome_msg db "Welcome to My Kernel!", 0
disk_error_msg db "Error loading kernel from disk!", 0

times 510 - ($ - $$) db 0   ; Fill up the rest of the sector with zeros
dw 0xAA55                   ; Boot signature
