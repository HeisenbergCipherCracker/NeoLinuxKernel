#!/bin/sh

set -e

AS=as
GCC=aarch64-none-elf-gcc
GCC_OPTIONS="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -masm=intel"
OBJ_FILES=""

echo "Compiling boot.s"
rm -f boot.o
$AS boot.s -o boot.o
OBJ_FILES="$OBJ_FILES boot.o"

# ... (repeat similar modifications for other assembly and C files)

echo "Linking"
rm -f myos.bin
echo "OBJ_FILES: $OBJ_FILES"
$GCC -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $OBJ_FILES -lgcc

echo "Building a bootable CD-ROM image"
if grub-file --is-x86-multiboot myos.bin; then
    echo "Multiboot confirmed"
else
    echo "The file is not multiboot"
    exit 1
fi
rm -rf isodir
mkdir -p isodir/boot/grub
cp -p myos.bin isodir/boot/myos.bin
cp -p grub.cfg isodir/boot/grub/grub.cfg

# Note: On macOS, the `grub-mkrescue` tool might not be available. We can use `xorriso` instead.
xorriso -as mkisofs -b boot/grub/myos.bin -no-emul-boot -boot-load-size 4 -o myos.iso isodir

echo "To test, please run: qemu-system-aarch64 -cdrom myos.iso"
