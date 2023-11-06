#include "usart.h"
#include "stm32g4xx.h"

void init_lpuart1(void)
{
    /* Init the pinpouts PA2/PA3 
        - Start the clock for AHB2 bus
        - Initialize the pins with mode alternate function and alternate function 12 (AF12)
    */
    RCC->AHB2ENR |= (1<<RCC_AHB2ENR_GPIOAEN_Pos);
    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;

    GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODE2_Pos | 0b10 << GPIO_MODER_MODE3_Pos);

    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk);
    GPIOA->AFR[0] |= (12 << GPIO_AFRL_AFSEL2_Pos | 12 << GPIO_AFRL_AFSEL3_Pos);

    /* Init the lpuart */
    RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
    dummy = RCC->CFGR;
    dummy = RCC->CFGR;
    RCC->APB1ENR2 |= (1<<RCC_APB1ENR2_LPUART1EN_Pos);
    dummy = RCC->APB1ENR2;
    dummy = RCC->APB1ENR2;
    LPUART1->CR1 &= ~(USART_CR1_UE);
    LPUART1->BRR = 0x3640E;
    LPUART1->PRESC &= ~(0xF);
    LPUART1->CR1 |= USART_CR1_UE;
    LPUART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

void usart_write(USART_TypeDef *usart, char c)
{
    usart->TDR = c;
    while(!(usart->ISR & USART_ISR_TC_Msk));
}

