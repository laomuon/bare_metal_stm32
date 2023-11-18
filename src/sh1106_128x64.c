#include "sh1106_128x64.h"
#include "stm32g474xx.h"

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
        ENTIRE_DISPLAY_OFF,
        NORMAL_DISPLAY,
        SET_SEGMENT_REMAP,
        SET_MULTIPLEX_RATION,
        63,
        DISPLAY_ON
    };
    oled_send_cmds(oled, 8, init_cmds);
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

void oled_clear_display(struct Oled oled)
{
    int cmds[4] = {START_COMMAND_MODE};
    int ram_data[133] = {START_DATA_MODE};
    cmds[1] = SET_LOW_COL_ADDR_HEADER + 0;
    cmds[2] = SET_HIGH_COL_ADDR_HEADER + 0;
    for (int draw_page=0; draw_page<8; draw_page++)
    {
        cmds[3] = SET_PAGE_ADDR_HEADER + draw_page;
        oled_send_cmds(oled, 4, cmds);
        oled_send_cmds(oled, 133, ram_data);
    }
}

void oled_draw_line(struct Oled oled, int line_nb)
{
    int cmds[4] = {START_COMMAND_MODE};
    int ram_data[133] = {START_DATA_MODE};
    int first_page_addr = (int)(line_nb / 8) % 8;
    int line_in_page = line_nb % 8;

    for (int i = 1; i < 133; i++)
    {
        ram_data[i] = 1 << line_in_page;
    }
    printf("%d \r\n", first_page_addr);
    cmds[1] = SET_LOW_COL_ADDR_HEADER + 0;
    cmds[2] = SET_HIGH_COL_ADDR_HEADER + 0;
    cmds[3] = SET_PAGE_ADDR_HEADER + first_page_addr;
    oled_clear_display(oled);
    oled_send_cmds(oled, 4, cmds);
    oled_send_cmds(oled, 133, ram_data);
}

