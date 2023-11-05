#include "i2c.h"
#include "stm32g474xx.h"

#define OLED_ADDR 0x3C << 1

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

void init_i2c1(void)
{
    init_pin_i2c1();
    I2C1->CR1 &= ~I2C_CR1_PE_Msk;

    // Disable analog and digital filters
    I2C1->CR1 &= ~(I2C_CR1_ANFOFF_Msk);
    I2C1->CR1 &= ~(I2C_CR1_DNF_Msk);

    // Set timings
    I2C1->TIMINGR &= ~(I2C_TIMINGR_PRESC_Msk);
    I2C1->TIMINGR &= ~(I2C_TIMINGR_SDADEL_Msk);
    I2C1->TIMINGR &= ~(I2C_TIMINGR_SCLDEL_Msk);
    I2C1->TIMINGR &= ~(I2C_TIMINGR_SCLH_Msk);
    I2C1->TIMINGR &= ~(I2C_TIMINGR_SCLL_Msk);

    I2C1->TIMINGR |= (1<<I2C_TIMINGR_PRESC_Pos);
    I2C1->TIMINGR |= 0x9 << I2C_TIMINGR_SCLL_Pos;
    I2C1->TIMINGR |= 0x3 << I2C_TIMINGR_SCLH_Pos;
    I2C1->TIMINGR |= 0x2 << I2C_TIMINGR_SDADEL_Pos;
    I2C1->TIMINGR |= 0x3 << I2C_TIMINGR_SCLDEL_Pos;

    // I2C1->TIMINGR = 0x10C0F1FF;
    I2C1->CR1 &= ~I2C_CR1_NOSTRETCH_Msk;

    // Disable DMA
    I2C1->CR1 &= ~I2C_CR1_RXDMAEN_Msk;
    I2C1->CR1 &= ~I2C_CR1_TXDMAEN_Msk;

    I2C1->OAR1 |= I2C_OAR1_OA1EN_Msk;
    I2C1->OAR1 |= I2C_OAR1_OA1MODE_Msk;
    I2C1->OAR1 &= ~I2C_OAR1_OA1_Msk;
    I2C1->OAR1 |= 0x78;

    I2C1->CR1 |= I2C_CR1_PE_Msk;
}

void start_i2c1(void)
{
    I2C1->CR2 &= ~(I2C_CR2_ADD10_Msk);
    I2C1->CR2 &= ~(I2C_CR2_SADD_Msk);
    I2C1->CR2 |= OLED_ADDR << I2C_CR2_SADD_Pos;
    I2C1->CR2 &= ~(I2C_CR2_RD_WRN_Msk);
    I2C1->CR2 &= ~I2C_CR2_NBYTES_Msk;
    I2C1->CR2 |= 5 << I2C_CR2_NBYTES_Pos;
    I2C1->CR2 |= I2C_CR2_AUTOEND_Msk;
    I2C1->CR2 |= 1 << I2C_CR2_START_Pos;
}

void i2c1_stop_transfert(void)
{
    I2C1->ICR |= I2C_ICR_STOPCF;
    I2C1->CR2 = 0;
}

void i2c1_transfert(int msg)
{
    start_i2c1();
    I2C1->TXDR = 0;
    while (!(I2C1->ISR & I2C_ISR_TXIS_Msk));
    I2C1->TXDR = 0b10101110;
    while (!(I2C1->ISR & I2C_ISR_TXIS_Msk));
    I2C1->TXDR = 0b10101111;
    while (!(I2C1->ISR & I2C_ISR_TXIS_Msk));
    I2C1->TXDR = 0b10100101;
    while (!(I2C1->ISR & I2C_ISR_TXIS_Msk));
    i2c1_stop_transfert();
    printf("done\n");
}
