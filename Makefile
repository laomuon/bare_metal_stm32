CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb --specs=nano.specs -g3 -Wall
CPPFLAGS= -I CMSIS/CMSIS/Core/Include/ \
		  -I CMSIS/Device/ST/STM32G4/Include/ \
		  -D STM32G474xx \
		  -I include
LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)
CONVERT_PROGRAM=arm-none-eabi-objcopy
FLASH_PROGRAM=st-flash
PRINT_FLOAT= -u _printf_float

all: blink.bin

blink.elf: startup.o main.o system_stm32g4xx.o syscall.o usart.o i2c.o sh1106_128x64.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(PRINT_FLOAT) $^ -o blink.elf

main.o: src/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/main.c -c

startup.o: src/startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/startup.c -c

system_stm32g4xx.o: CMSIS/Device/ST/STM32G4/Source/Templates/system_stm32g4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) CMSIS/Device/ST/STM32G4/Source/Templates/system_stm32g4xx.c -c

syscall.o: src/syscall.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/syscall.c -c

usart.o: src/usart.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/usart.c -c

i2c.o: src/i2c.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/i2c.c -c

sh1106_128x64.o: src/sh1106_128x64.c
	$(CC) $(CFLAGS) $(CPPFLAGS) src/sh1106_128x64.c -c

blink.bin: blink.elf
	$(CONVERT_PROGRAM) -O binary blink.elf blink.bin

flash: blink.bin
	$(FLASH_PROGRAM) --reset --connect-under-reset write blink.bin 0x8000000

.PHONY: clean
clean:
	rm -f *.o *.elf *.bin

