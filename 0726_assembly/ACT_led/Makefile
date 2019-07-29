SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -O2 -Wall -Wextra -fpic -ffreestanding -std=gnu99

all: clean kernel.bin

boot.o: boot.S
	arm-none-eabi-gcc $(CFLAGS) -c boot.S -o boot.o

kernel.bin: boot.o $(OBJS)
	arm-none-eabi-gcc -T linker.ld -o kernel.elf -ffreestanding -O2 -nostdlib boot.o
	arm-none-eabi-objcopy kernel.elf -O binary kernel.bin
	arm-none-eabi-objdump -D kernel.elf > kernel.dump

clean:
	rm kernel.elf kernel.bin *.o > /dev/null 2>/dev/null || true
