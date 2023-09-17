#define SRAM_START (0x20000000U)
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
/* The main stack pointer address must then be stored as the first word in the interrupt vector table
   It should also be init to point at the end of SRAM and then move "down" in memory */
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

#include <stdint.h>
/* 16 words for system exception handler and 102 for interrupt handler */
#define ISR_VECTOR_SIZE_WORDS 118

void main(void);
void __libc_init_array();

void reset_handler(void);
/* default handler function for un-implemented handler */
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mem_manage_handler(void) __attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void syscall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));
void wwdg_irqhandler(void) __attribute__((weak, alias("default_handler")));
void pvd_pvm_irqhandler(void) __attribute__((weak, alias("default_handler")));
void rtc_tamp_csslse_irqhandler(void) __attribute__((weak, alias("default_handler")));
void rtc_wkup_irqhandler(void) __attribute__((weak, alias("default_handler")));
void flash_irqhandler(void) __attribute__((weak, alias("default_handler")));
void rcc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti0_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch6_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch7_irqhandler(void) __attribute__((weak, alias("default_handler")));
void adc1_2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usb_hp_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usb_lp_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan1_it0_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan1_it1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti9_5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim1_brk_tim15_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim1_up_tim16_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim17_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim1_cc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c1_ev_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c1_er_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c2_ev_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c2_er_irqhandler(void) __attribute__((weak, alias("default_handler")));
void spi1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void spi2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usart1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usart2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usart3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void exti15_10_irqhandler(void) __attribute__((weak, alias("default_handler")));
void rtc_alarm_irqhandler(void) __attribute__((weak, alias("default_handler")));
void usbwakeup_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim8_brk_terr_ierr_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim8_up_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim8_trgcom_dir_idx_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim8_cc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void adc3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fsmc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void lptim1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void spi3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void uart4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void uart5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim6_dac_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim7_dac_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch2_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void adc4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void adc5_irqhandler(void) __attribute__((weak, alias("default_handler")));
void ucpd1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void comp1_2_3_irqhandler(void) __attribute__((weak, alias("default_handler")));
void comp4_5_6_irqhandler(void) __attribute__((weak, alias("default_handler")));
void comp7_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_master_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_tima_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_timb_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_timc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_timd_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_time_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_tim_flt_irqhandler(void) __attribute__((weak, alias("default_handler")));
void hrtim_timf_irqhandler(void) __attribute__((weak, alias("default_handler")));
void crs_irqhandler(void) __attribute__((weak, alias("default_handler")));
void sai_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim20_brk_terr_ierr_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim20_up_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim20_trgcom_dir_idx_irqhandler(void) __attribute__((weak, alias("default_handler")));
void tim20_cc_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fpu_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c4_ev_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c4_er_irqhandler(void) __attribute__((weak, alias("default_handler")));
void spi4_irqhandler(void) __attribute__((weak, alias("default_handler")));
void aes_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan2_it0_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan2_it1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan3_it0_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fdcan3_it1_irqhandler(void) __attribute__((weak, alias("default_handler")));
void rng_irqhandler(void) __attribute__((weak, alias("default_handler")));
void lpuart_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c3_ev_irqhandler(void) __attribute__((weak, alias("default_handler")));
void i2c3_er_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dmamux_ovr_irqhandler(void) __attribute__((weak, alias("default_handler")));
void quadspi_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma1_ch8_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch6_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch7_irqhandler(void) __attribute__((weak, alias("default_handler")));
void dma2_ch8_irqhandler(void) __attribute__((weak, alias("default_handler")));
void cordic_irqhandler(void) __attribute__((weak, alias("default_handler")));
void fmac_irqhandler(void) __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
    STACK_POINTER_INIT_ADDRESS,
    (uint32_t)&reset_handler,
    (uint32_t)&nmi_handler,
    (uint32_t)&hard_fault_handler,
    (uint32_t)&mem_manage_handler,
    (uint32_t)&bus_fault_handler,
    (uint32_t)&usage_fault_handler,
    0,
    0,
    0,
    0,
    (uint32_t)&syscall_handler,
    (uint32_t)&debug_monitor_handler,
    0,
    (uint32_t)&pendsv_handler,
    (uint32_t)&systick_handler,
    (uint32_t)&wwdg_irqhandler,
    (uint32_t)&pvd_pvm_irqhandler,
    (uint32_t)&rtc_tamp_csslse_irqhandler,
    (uint32_t)&rtc_wkup_irqhandler,
    (uint32_t)&flash_irqhandler,
    (uint32_t)&rcc_irqhandler,
    (uint32_t)&exti0_irqhandler,
    (uint32_t)&exti1_irqhandler,
    (uint32_t)&exti2_irqhandler,
    (uint32_t)&exti3_irqhandler,
    (uint32_t)&exti4_irqhandler,
    (uint32_t)&dma1_ch1_irqhandler,
    (uint32_t)&dma1_ch2_irqhandler,
    (uint32_t)&dma1_ch3_irqhandler,
    (uint32_t)&dma1_ch4_irqhandler,
    (uint32_t)&dma1_ch5_irqhandler,
    (uint32_t)&dma1_ch6_irqhandler,
    (uint32_t)&dma1_ch7_irqhandler,
    (uint32_t)&adc1_2_irqhandler,
    (uint32_t)&usb_hp_irqhandler,
    (uint32_t)&usb_lp_irqhandler,
    (uint32_t)&fdcan1_it0_irqhandler,
    (uint32_t)&fdcan1_it1_irqhandler,
    (uint32_t)&exti9_5_irqhandler,
    (uint32_t)&tim1_brk_tim15_irqhandler,
    (uint32_t)&tim1_up_tim16_irqhandler,
    (uint32_t)&tim1_trg_com_tim17_irqhandler,
    (uint32_t)&tim1_cc_irqhandler,
    (uint32_t)&tim2_irqhandler,
    (uint32_t)&tim3_irqhandler,
    (uint32_t)&tim4_irqhandler,
    (uint32_t)&i2c1_ev_irqhandler,
    (uint32_t)&i2c1_er_irqhandler,
    (uint32_t)&i2c2_ev_irqhandler,
    (uint32_t)&i2c2_er_irqhandler,
    (uint32_t)&spi1_irqhandler,
    (uint32_t)&spi2_irqhandler,
    (uint32_t)&usart1_irqhandler,
    (uint32_t)&usart2_irqhandler,
    (uint32_t)&usart3_irqhandler,
    (uint32_t)&exti15_10_irqhandler,
    (uint32_t)&rtc_alarm_irqhandler,
    (uint32_t)&usbwakeup_irqhandler,
    (uint32_t)&tim8_brk_terr_ierr_irqhandler,
    (uint32_t)&tim8_up_irqhandler,
    (uint32_t)&tim8_trgcom_dir_idx_irqhandler,
    (uint32_t)&tim8_cc_irqhandler,
    (uint32_t)&adc3_irqhandler,
    (uint32_t)&fsmc_irqhandler,
    (uint32_t)&lptim1_irqhandler,
    (uint32_t)&tim5_irqhandler,
    (uint32_t)&spi3_irqhandler,
    (uint32_t)&uart4_irqhandler,
    (uint32_t)&uart5_irqhandler,
    (uint32_t)&tim6_dac_irqhandler,
    (uint32_t)&tim7_dac_irqhandler,
    (uint32_t)&dma2_ch1_irqhandler,
    (uint32_t)&dma2_ch2_irqhandler,
    (uint32_t)&dma2_ch3_irqhandler,
    (uint32_t)&dma2_ch4_irqhandler,
    (uint32_t)&dma2_ch5_irqhandler,
    (uint32_t)&adc4_irqhandler,
    (uint32_t)&adc5_irqhandler,
    (uint32_t)&ucpd1_irqhandler,
    (uint32_t)&comp1_2_3_irqhandler,
    (uint32_t)&comp4_5_6_irqhandler,
    (uint32_t)&comp7_irqhandler,
    (uint32_t)&hrtim_master_irqhandler,
    (uint32_t)&hrtim_tima_irqhandler,
    (uint32_t)&hrtim_timb_irqhandler,
    (uint32_t)&hrtim_timc_irqhandler,
    (uint32_t)&hrtim_timd_irqhandler,
    (uint32_t)&hrtim_time_irqhandler,
    (uint32_t)&hrtim_tim_flt_irqhandler,
    (uint32_t)&hrtim_timf_irqhandler,
    (uint32_t)&crs_irqhandler,
    (uint32_t)&sai_irqhandler,
    (uint32_t)&tim20_brk_terr_ierr_irqhandler,
    (uint32_t)&tim20_up_irqhandler,
    (uint32_t)&tim20_trgcom_dir_idx_irqhandler,
    (uint32_t)&tim20_cc_irqhandler,
    (uint32_t)&fpu_irqhandler,
    (uint32_t)&i2c4_ev_irqhandler,
    (uint32_t)&i2c4_er_irqhandler,
    (uint32_t)&spi4_irqhandler,
    (uint32_t)&aes_irqhandler,
    (uint32_t)&fdcan2_it0_irqhandler,
    (uint32_t)&fdcan2_it1_irqhandler,
    (uint32_t)&fdcan3_it0_irqhandler,
    (uint32_t)&fdcan3_it1_irqhandler,
    (uint32_t)&rng_irqhandler,
    (uint32_t)&lpuart_irqhandler,
    (uint32_t)&i2c3_ev_irqhandler,
    (uint32_t)&i2c3_er_irqhandler,
    (uint32_t)&dmamux_ovr_irqhandler,
    (uint32_t)&quadspi_irqhandler,
    (uint32_t)&dma1_ch8_irqhandler,
    (uint32_t)&dma2_ch6_irqhandler,
    (uint32_t)&dma2_ch7_irqhandler,
    (uint32_t)&dma2_ch8_irqhandler,
    (uint32_t)&cordic_irqhandler,
    (uint32_t)&fmac_irqhandler,
};

void default_handler(void)
{
    while(1);
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void reset_handler(void)
{
    // Copy .data from FLASH to SRAM
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *flash_data = (uint8_t*) &_etext; // Data load address (in flash)
    uint8_t *sram_data = (uint8_t*) &_sdata; // Data virtual address (in sram)

    for (uint32_t i = 0; i < data_size; i++)
    {
        sram_data[i] = flash_data[i];
    }

    // Zero-fill .bss section in SRAM
    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t *bss = (uint8_t*) &_sbss;

    for (uint32_t i = 0; i < bss_size; i++)
    {
        bss[i] = 0;
    }

    __libc_init_array();
    main();
}
