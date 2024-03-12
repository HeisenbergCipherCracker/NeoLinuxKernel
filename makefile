# Makefile

boot.bin: boot.asm
    nasm -f bin boot.asm -o boot.bin

kernel_entry.bin: kernel_entry.asm
    nasm -f bin kernel_entry.asm -o kernel_entry.bin

kernel.bin: linker.ld kernel_entry.bin
    ld -T linker.ld -o kernel.bin kernel_entry.bin

os_image.img: boot.bin kernel.bin
    cat boot.bin kernel.bin > os_image.img

clean:
    rm -f boot.bin kernel_entry.bin kernel.bin os_image.img
