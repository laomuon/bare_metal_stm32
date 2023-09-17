CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb --specs=nano.specs -g3 -Wall
CPPFLAGS= -I CMSIS/CMSIS/Core/Include/ \
		  -I CMSIS/Device/ST/STM32G4/Include/ \
		  -D STM32G474xx
LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)
CONVERT_PROGRAM=arm-none-eabi-objcopy
FLASH_PROGRAM=st-flash

all: blink.bin

blink.elf: startup.o main.o system_stm32g4xx.o syscall.o usart.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o blink.elf

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32g4xx.o: CMSIS/Device/ST/STM32G4/Source/Templates/system_stm32g4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) CMSIS/Device/ST/STM32G4/Source/Templates/system_stm32g4xx.c -c

syscall.o: syscall.c
	$(CC) $(CFLAGS) $(CPPFLAGS) syscall.c -c

usart.o: usart.c
	$(CC) $(CFLAGS) $(CPPFLAGS) usart.c -c

blink.bin: blink.elf
	$(CONVERT_PROGRAM) -O binary blink.elf blink.bin

flash: blink.bin
	$(FLASH_PROGRAM) --reset write blink.bin 0x8000000

.PHONY: clean
clean:
	rm -f *.o *.elf *.bin

