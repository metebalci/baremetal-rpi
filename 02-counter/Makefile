
APP = counter

all:
	rm -rf $(APP).elf $(APP).bin
	aarch64-elf-as -o $(APP).elf $(APP).s
	aarch64-elf-objcopy -O binary $(APP).elf $(APP).bin
