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
        . = ALIGN(4)
        _etext = .;
    } >FLASH

    /* Constant (read-only) data */
    .rodata :
    {
        . = ALIGN(4)
        *(.rodata)
        . = ALIGN(4)
    } >FLASH

    /* Initialized variable data that will be copied to SRAM during setup */
    .data :
    {
        . = ALIGN(4)
        _sdata = .;
        *(.data)
        . = ALIGN(4)
        _edata = .;
    } >SRAM AT> FLASH

    /* Uninitialized variable data, zero-filled during setup */
    .bss :
    {
        . = ALIGN(4)
        _sbss = .;
        *(.bss)
        . = ALIGN(4)
        _ebss = .;

    } >SRAM

}
