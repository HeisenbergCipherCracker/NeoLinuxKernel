TARGET = kernel
CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -std=c11 -ffreestanding -nostdlib -m32
LDFLAGS = -T linker.ld -melf_i386

SRCS = kernel.c
OBJS = $(SRCS:.c=.o)

$(TARGET).bin: $(OBJS)
    $(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET).bin
