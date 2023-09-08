#include <stdint.h>

#define AHB2_BASE (0x48000000U)
#define GPIOA_BASE (AHB2_BASE + 0x0U)
#define AHB1_BASE (0x40020000U)
#define RCC_BASE (AHB1_BASE + 0x1000U)
#define RCC_AHB2ENR_OFFSET 0x4CU

#define RCC_AHB2ENR ((volatile uint32_t*)(RCC_AHB2ENR_OFFSET + RCC_BASE))
#define RCC_AHB2ENR_GPIOAEN 0x0U

#define GPIO_MODER_OFFSET 0x0U
#define GPIOA_MODER ((volatile uint32_t*)(GPIOA_BASE + GPIO_MODER_OFFSET))

#define GPIO_MODER_MODER5_OFFSET 10U

#define GPIO_ODR_OFFSET 0x14U
#define GPIOA_ODR ((volatile uint32_t*)(GPIOA_BASE + GPIO_ODR_OFFSET))

#define LED_PIN 5

void main(void)
{
    *RCC_AHB2ENR |= (1<<RCC_AHB2ENR_GPIOAEN);

    volatile uint32_t dummy;
    dummy = *(RCC_AHB2ENR);
    dummy = *(RCC_AHB2ENR);

    *GPIOA_MODER &= ~(3<<GPIO_MODER_MODER5_OFFSET);
    *GPIOA_MODER |= (1<<GPIO_MODER_MODER5_OFFSET);
    while(1)
    {
        *GPIOA_ODR ^= (1<<LED_PIN);

        for (uint32_t i=0; i<1000000; i++);
    }
}

