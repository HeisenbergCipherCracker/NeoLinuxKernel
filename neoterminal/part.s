[bits 16]
[org 0x0600]
 
start:
  cli                         ; We do not want to be interrupted
  xor ax, ax                  ; 0 AX
  mov ds, ax                  ; Set Data Segment to 0
  mov es, ax                  ; Set Extra Segment to 0
  mov ss, ax                  ; Set Stack Segment to 0
  mov sp, ax                  ; Set Stack Pointer to 0
  .CopyLower:
    mov cx, 0x0100            ; 256 WORDs in MBR
    mov si, 0x7C00            ; Current MBR Address
    mov di, 0x0600            ; New MBR Address
    rep movsw                 ; Copy MBR
  jmp 0:LowStart              ; Jump to new Address
 
LowStart:
  sti                         ; Start interrupts
  mov BYTE [bootDrive], dl    ; Save BootDrive
  .CheckPartitions:           ; Check Partition Table For Bootable Partition
    mov bx, PT1               ; Base = Partition Table Entry 1
    mov cx, 4                 ; There are 4 Partition Table Entries
    .CKPTloop:
      mov al, BYTE [bx]       ; Get Boot indicator bit flag
      test al, 0x80           ; Check For Active Bit
      jnz .CKPTFound          ; We Found an Active Partition
      add bx, 0x10            ; Partition Table Entry is 16 Bytes
      dec cx                  ; Decrement Counter
      jnz .CKPTloop           ; Loop
    jmp ERROR                 ; ERROR!
    .CKPTFound:
      mov WORD [PToff], bx    ; Save Offset
      add bx, 8               ; Increment Base to LBA Address
  .ReadVBR:
    mov EBX, DWORD [bx]       ; Start LBA of Active Partition
    mov di, 0x7C00            ; We Are Loading VBR to 0x07C0:0x0000
    mov cx, 1                 ; Only one sector
    call ReadSectors          ; Read Sector
 
  .jumpToVBR:
    cmp WORD [0x7DFE], 0xAA55 ; Check Boot Signature
    jne ERROR                 ; Error if not Boot Signature
    mov si, WORD [PToff]      ; Set DS:SI to Partition Table Entry
    mov dl, BYTE [bootDrive]  ; Set DL to Drive Number
    jmp 0x7C00                ; Jump To VBR
 
times (218 - ($-$$)) nop      ; Pad for disk time stamp
 
DiskTimeStamp times 8 db 0    ; Disk Time Stamp
 
bootDrive db 0                ; Our Drive Number Variable
PToff dw 0                    ; Our Partition Table Entry Offset
 
times (0x1b4 - ($-$$)) nop    ; Pad For MBR Partition Table
 
UID times 10 db 0             ; Unique Disk ID
PT1 times 16 db 0             ; First Partition Entry
PT2 times 16 db 0             ; Second Partition Entry
PT3 times 16 db 0             ; Third Partition Entry
PT4 times 16 db 0             ; Fourth Partition Entry
 
dw 0xAA55                     ; Boot Signature