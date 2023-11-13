#include "stm32g474xx.h"

void init_i2c(I2C_TypeDef *i2c);
void start_i2c(I2C_TypeDef *i2c, int addr);
void i2c_transfert(I2C_TypeDef *i2c, int *msg, int len, int addr);
