#include "i2c.h"

#define START_COMMAND_MODE 0
#define DISPLAY_OFF 0b10101110
#define DISPLAY_ON 0b10101111
#define ENTIRE_DISPLAY_ON 0b10100101
#define ENTIRE_DISPLAY_OFF 0b10100100

struct Oled
{
    I2C_TypeDef *hi2c;
    int addr;
};

void init_oled(struct Oled oled);
void oled_send_cmds(struct Oled oled, int lenght, int *commands);
void oled_entire_display_control(struct Oled oled, int is_on);
