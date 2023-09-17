#include "usart.h"
#include "stm32g4xx.h"

int init_lpuart1(void)
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
    RCC->APB1ENR2 |= (1<<RCC_APB1ENR2_LPUART1EN_Pos);
    dummy = RCC->APB1ENR2;
    dummy = RCC->APB1ENR2;
    // if (!(RCC->CR & RCC_CR_HSION_Msk)) return 0;
    // PWR->CR1 |= PWR_CR1_DBP_Msk;
    // dummy = PWR->CR1;
    // dummy = PWR->CR1;
    // RCC->BDCR |= RCC_BDCR_LSEON;
    // dummy = RCC->BDCR;
    // dummy = RCC->BDCR;
    // RCC->CCIPR |= 1 << RCC_CCIPR_LPUART1SEL_Pos;
    // dummy = RCC->CCIPR;
    // dummy = RCC->CCIPR;
    LPUART1->CR1 &= ~(USART_CR1_UE);
    LPUART1->BRR = 35556;
    LPUART1->PRESC &= ~(0xF);
    LPUART1->CR1 |= USART_CR1_UE;
    LPUART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

void usart_write(USART_TypeDef *usart, char c)
{
    usart->TDR = c;
    while(!(usart->ISR & USART_ISR_TC_Msk));
}

