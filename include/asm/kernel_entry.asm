; kernel_entry.asm
BITS 32    ; 32-bit code

global kmain   ; Make kmain globally accessible

kmain:
  ; Your kernel code starts here
  mov edx, welcome_msg
  call print_string

  jmp $        ; Infinite loop

print_string:
  mov eax, 0x0E        ; BIOS function for tty output
  mov ebx, 0x00000007  ; Page number and text attribute (white on black)
  mov ecx, edx         ; Point ECX to the string
  mov ah, 0x0E
.loop:
  lodsb                ; Load the next byte from string into AL
  test al, al          ; Check for null terminator
  jz .done             ; If null, end of string
  int 0x10             ; Otherwise, print the character
  jmp .loop            ; Repeat for the next character
.done:
  ret

welcome_msg db "Hello, World!", 0
