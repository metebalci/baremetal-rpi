
CFLAGS = -Wall -O2 -ffreestanding
LDFLAGS =-nostdlib -T link.ld

APP = uart

all: $(APP).elf

$(APP).elf: uart.o
	aarch64-elf-ld $(LDFLAGS) $(APP).o -o $(APP).elf
	aarch64-elf-objcopy -O binary $(APP).elf $(APP).bin

%.o: %.c
	aarch64-elf-gcc $(CFLAGS) -c $< -o $@

dump: $(APP).elf
	aarch64-elf-objdump -D $(APP).elf 

clean:
	rm -rf *.o *.elf *.bin
