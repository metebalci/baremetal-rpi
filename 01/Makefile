
all:
	rm -rf halt.elf halt.bin
	aarch64-elf-as -o halt.elf halt.s
	aarch64-elf-objcopy -O binary halt.elf halt.bin
