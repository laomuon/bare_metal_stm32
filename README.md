## Bare metal stm32

This repository is for me to figure out how to develop on stm32 without an IDE (STM32Cube, ...) or external library (HAL, LL, ..). The only library that I use is [CMSIS_5](https://github.com/ARM-software/CMSIS_5) where all registers are defined with easy to find names and Newlib-nano.

## Main goal
The end goal of this project is to develop my own driver for a module SSH1106 OLED that I own. It already exsits but I just want to go through the whole process, hoping that I will learn something new. All the tools I use are natives, access through the terminal

## What have been done
- Build the linker script
- Define the startup code in `startup.c`
- Build the `Makefile`
- Configure the clock system to be 100MHz
- Implement a primitive printf with `USART`
- Implement I2C
- Add a function to draw a line
- Add a function to draw a char
- Add a function to draw a string

## Tools
- [ARM GNU toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [stlink](https://github.com/stlink-org/stlink)
- [Bear](https://github.com/rizsotto/Bear) to generate the `compile_commands.json` for `clangd`
- make
- [minicom](https://help.ubuntu.com/community/Minicom) to view the message sent by the `USART`

## Library
- Newlib-nano
- [CMSIS](https://github.com/ARM-software/CMSIS_5)

## Instruction
- Clone the project
- Install `stlink` and `ARM GNU toolchain`
- `make && make flash`
