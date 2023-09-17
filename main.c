#include <stdint.h>
#include <stdio.h>
#include "stm32g4xx.h"
#include "usart.h"
#include <string.h>

#define LED_PIN 5

void main(void)
{
    RCC->AHB2ENR |= (1<<RCC_AHB2ENR_GPIOAEN_Pos);

    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;

    GPIOA->MODER &= ~(3<<GPIO_MODER_MODE5_Pos);
    GPIOA->MODER |= (1<<GPIO_MODER_MODE5_Pos);
    if (!(init_lpuart1())) return;
    while(1)
    {
        GPIOA->ODR ^= (1<<LED_PIN);
        printf("Test now\r\n");

        for (uint32_t i=0; i<1000000; i++);
    }
}

