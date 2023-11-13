#include "sh1106_128x64.h"

void oled_send_cmds(struct Oled oled, int lenght, int *commands)
{
    i2c_transfert(oled.hi2c, commands, lenght, oled.addr);
}

void init_oled(struct Oled oled)
{
    init_i2c(oled.hi2c);
    int init_cmds[] = {
        START_COMMAND_MODE,
        DISPLAY_OFF,
        DISPLAY_ON
    };
    oled_send_cmds(oled, 3, init_cmds);
}

void oled_entire_display_control(struct Oled oled, int is_on)
{
    int cmd[2];
    cmd[0] = START_COMMAND_MODE;
    if (is_on)
    {
        cmd[1] = ENTIRE_DISPLAY_ON;
    }
    else
    {
        cmd[1] = ENTIRE_DISPLAY_OFF;
    }
    oled_send_cmds(oled, 2, cmd);
}
