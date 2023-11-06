#include "stm32g474xx.h"

struct Oled
{
    struct I2C_TypeDef *hi2c;
    int addr;
};
