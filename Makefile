# Variables for compiler and flags
CC = i686-elf-gcc
AS = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -g -c
LDFLAGS = -ffreestanding -nostdlib -g -T linker.ld
LIBS = -lgcc

# Define the object files
OBJ = start.o kernel.o

# The default rule (first rule is run when you just type 'make')
all: mykernel.elf

# Link the kernel
mykernel.elf: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o mykernel.elf $(LIBS)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Assemble assembly files (using gcc as the wrapper)
%.o: %.s
	$(AS) $(CFLAGS) $< -o $@

# Run the kernel in QEMU
run: mykernel.elf
	qemu-system-i386 -kernel mykernel.elf

# Clean up build files
clean:
	rm -f *.o mykernel.elf
