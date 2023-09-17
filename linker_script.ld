ENTRY(reset_handler)

MEMORY
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    /* The start up code */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    /* The program code */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *(.eh_frame)
        *(.ARM.exidx)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    _sidata = LOADADDR(.data);

    /* Initialized variable data that will be copied to SRAM during setup */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        KEEP(*(.init_array))
        KEEP(*(.fini_array))
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT> FLASH

    /* Uninitialized variable data, zero-filled during setup */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;

    } >SRAM

}
