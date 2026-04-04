# Toolchain
CC      := i686-elf-gcc
AS      := i686-elf-gcc
LD      := i686-elf-gcc

CFLAGS  := -std=gnu99 -ffreestanding -g -Wall -Wextra
LDFLAGS := -ffreestanding -nostdlib -g -T linker.ld
LIBS    := -lgcc

ISO     := spencerOS.iso
TARGET  := spencerOS.elf

# Source collection
C_SOURCES  := $(shell find kernel arch drivers libk -name "*.c")
AS_SOURCES := $(shell find kernel arch drivers libk -name "*.s")

# Object files mirrored under build/
C_OBJECTS  := $(patsubst %.c, build/%.o, $(C_SOURCES))
AS_OBJECTS := $(patsubst %.s, build/%.o, $(AS_SOURCES))

OBJECTS := $(C_OBJECTS) $(AS_OBJECTS)

# Include paths
INCLUDES := -I. -Iarch -Idrivers/vga -Ilibk/include

.PHONY: all iso run clean

all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

# Compile .c
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Assemble .s
build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(CFLAGS) -c $< -o $@

# Build ISO
iso: $(TARGET)
	cp $(TARGET) iso/boot/spencerOS.elf
	grub-mkrescue -o $(ISO) iso/

# Run
run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

run-iso: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

# Clean
clean:
	rm -rf build/ $(TARGET) $(ISO)
