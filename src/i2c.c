#include "i2c.h"


void init_pin_i2c1(void)
{
    // Set the clock source to HSI16
    RCC->CR |= (1 << RCC_CR_HSION_Pos);
    while (!(RCC->CR & RCC_CR_HSIRDY_Msk));
    RCC->CCIPR &= ~(RCC_CCIPR_I2C1SEL_Msk);
    RCC->CCIPR |= 0b10 << RCC_CCIPR_I2C1SEL_Pos;

    RCC->AHB2ENR |= (1<<RCC_AHB2ENR_GPIOAEN_Pos);
    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;

    RCC->AHB2ENR |= (1<<RCC_AHB2ENR_GPIOBEN_Pos);
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;

    GPIOA->MODER &= ~(GPIO_MODER_MODE15_Msk);
    GPIOA->MODER |= 0b10 << GPIO_MODER_MODE15_Pos;

    GPIOA->OTYPER |= GPIO_OTYPER_OT15_Msk;

    GPIOB->MODER &= ~(GPIO_MODER_MODE7_Msk);
    GPIOB->MODER |= 0b10 << GPIO_MODER_MODE7_Pos;

    GPIOB->OTYPER |= GPIO_OTYPER_OT7_Msk;

    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL15_Msk);
    GPIOA->AFR[1] |= 0b0100 << GPIO_AFRH_AFSEL15_Pos;

    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL7_Msk);
    GPIOB->AFR[0] |= 0b0100 << GPIO_AFRL_AFSEL7_Pos;

    RCC->APB1ENR1 |= (1 << RCC_APB1ENR1_I2C1EN_Pos);
    dummy = RCC->APB1ENR1;
    dummy = RCC->APB1ENR1;
    //
}

void init_i2c(I2C_TypeDef *i2c)
{
    init_pin_i2c1();
    i2c->CR1 &= ~I2C_CR1_PE_Msk;

    // Disable analog and digital filters
    i2c->CR1 &= ~(I2C_CR1_ANFOFF_Msk);
    i2c->CR1 &= ~(I2C_CR1_DNF_Msk);

    // Set timings
    i2c->TIMINGR &= ~(I2C_TIMINGR_PRESC_Msk);
    i2c->TIMINGR &= ~(I2C_TIMINGR_SDADEL_Msk);
    i2c->TIMINGR &= ~(I2C_TIMINGR_SCLDEL_Msk);
    i2c->TIMINGR &= ~(I2C_TIMINGR_SCLH_Msk);
    i2c->TIMINGR &= ~(I2C_TIMINGR_SCLL_Msk);

    i2c->TIMINGR |= (1<<I2C_TIMINGR_PRESC_Pos);
    i2c->TIMINGR |= 0x9 << I2C_TIMINGR_SCLL_Pos;
    i2c->TIMINGR |= 0x3 << I2C_TIMINGR_SCLH_Pos;
    i2c->TIMINGR |= 0x2 << I2C_TIMINGR_SDADEL_Pos;
    i2c->TIMINGR |= 0x3 << I2C_TIMINGR_SCLDEL_Pos;

    i2c->CR1 &= ~I2C_CR1_NOSTRETCH_Msk;

    // Disable DMA
    i2c->CR1 &= ~I2C_CR1_RXDMAEN_Msk;
    i2c->CR1 &= ~I2C_CR1_TXDMAEN_Msk;

    i2c->OAR1 |= I2C_OAR1_OA1EN_Msk;
    i2c->OAR1 |= I2C_OAR1_OA1MODE_Msk;
    i2c->OAR1 &= ~I2C_OAR1_OA1_Msk;
    i2c->OAR1 |= 0x78;

    i2c->CR1 |= I2C_CR1_PE_Msk;
}

void start_i2c(I2C_TypeDef *i2c, int addr)
{
    i2c->CR2 &= ~(I2C_CR2_ADD10_Msk);
    i2c->CR2 &= ~(I2C_CR2_SADD_Msk);
    i2c->CR2 |= addr << I2C_CR2_SADD_Pos;
    i2c->CR2 &= ~(I2C_CR2_RD_WRN_Msk);
    i2c->CR2 &= ~I2C_CR2_NBYTES_Msk;
    i2c->CR2 |= 5 << I2C_CR2_NBYTES_Pos;
    i2c->CR2 |= I2C_CR2_AUTOEND_Msk;
    i2c->CR2 |= 1 << I2C_CR2_START_Pos;
}

void i2c_stop_transfert(I2C_TypeDef *i2c)
{
    i2c->ICR |= I2C_ICR_STOPCF;
    i2c->CR2 = 0;
}

void i2c_transfert(I2C_TypeDef *i2c, int *msg, int len, int addr)
{
    start_i2c(i2c, addr);
    for (int i =0; i < len; i++)
    {
        i2c->TXDR = msg[i];
        while (!(i2c->ISR & I2C_ISR_TXIS_Msk));
    }
    i2c_stop_transfert(i2c);
}
