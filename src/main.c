#include <stdint.h>
#include "usart.h"
#include "sh1106_128x64.h"

#define LED_PIN 5
#define OLED_ADDR 0x3C << 1

/* Switch from power Range 2 (Low power) to Range 1 Normal (High Power) */
void init_pwr(void)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN_Msk;
    volatile uint32_t dummy;
    dummy = RCC->APB1ENR1;
    dummy = RCC->APB1ENR1;
    PWR->CR1 |= PWR_CR1_VOS_1;
    while(PWR->SR2 & PWR_SR2_VOSF_Msk);
    RCC->AHB1ENR |= RCC_AHB1ENR_FLASHEN_Msk;
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;
    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
    dummy = FLASH->ACR;
    dummy = FLASH->ACR;
    PWR->CR5 |= PWR_CR5_R1MODE_Msk;
}

/* Set the clock SYSCLK to 100MHz */
void init_clock(void)
{
    RCC->CR &= ~(RCC_CR_PLLON_Msk);
    while((RCC->CR & RCC_CR_PLLRDY_Msk));

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;  // M=1
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
    RCC->PLLCFGR |= 25 << RCC_PLLCFGR_PLLN_Pos;  // N=25
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR_Msk;
    RCC->PLLCFGR |= 1 << RCC_PLLCFGR_PLLR_Pos;  // R=4
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_Msk;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI_Msk; // Set PLL input as HSI16

    RCC->CR |= RCC_CR_PLLON_Msk;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN_Msk;

    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV2;
    RCC->CFGR &= ~RCC_CFGR_SW_Msk;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    volatile uint32_t dummy;
    dummy = RCC->CFGR;
    dummy = RCC->CFGR;
    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    dummy = RCC->CFGR;
    dummy = RCC->CFGR;
}

uint32_t tick;
/* Reimplement the handler in startup.c */
void systick_handler()
{
    tick++;
}

void delay_ms(uint32_t miliseconds)
{
    uint32_t start = tick;
    uint32_t end = start + miliseconds;

    if (end < start)
    {
        while (tick > start); // wait for tick to wrap around 0
    }
    while (tick < end);
}

int main(void)
{
    struct Oled oled = {I2C1, OLED_ADDR};
    init_pwr();
    init_clock();
    RCC->AHB2ENR |= (1<<RCC_AHB2ENR_GPIOAEN_Pos);
    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;

    GPIOA->MODER &= ~(3<<GPIO_MODER_MODE5_Pos);
    GPIOA->MODER |= (1<<GPIO_MODER_MODE5_Pos);
    init_lpuart1();
    printf("%d\r\n", oled.hi2c->CR1);
    init_oled(oled);
    oled_entire_display_control(oled, 1);
    SysTick_Config(100000);
    __enable_irq();
    while(1)
    {
        GPIOA->ODR ^= (1<<LED_PIN);
        /* printf need a \n character at the end as stdout is buffered
        https://community.st.com/t5/stm32cubeide-mcus/printf-not-working-write-never-gets-called/td-p/276659
        */
        printf("[%.3f] Hello World\r\n", (float)tick/1000.0f);
        delay_ms(1000);

    }

    return 1;
}
