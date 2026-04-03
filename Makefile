# Variables for compiler and flags
CC = i686-elf-gcc
AS = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -g -c
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld
LIBS = -lgcc

# Define the object files
OBJ = start.o gdt.o load_gdt.o idt.o load_idt pic.o kernel.o

# The default rule (first rule is run when you just type 'make')
all: spencerOS.elf

# Link the kernel
spencerOS.elf: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o spencerOS.elf $(LIBS)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Assemble assembly files (using gcc as the wrapper)
%.o: %.s
	$(AS) $(CFLAGS) $< -o $@

# Run the kernel in QEMU
run: spencerOS.elf
	qemu-system-i386 -kernel spencerOS.elf

# Clean up build files
clean:
	rm -f *.o spencerOS.elf
