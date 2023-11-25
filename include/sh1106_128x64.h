#include "i2c.h"
#include "font.h"

#define START_COMMAND_MODE 0
#define START_DATA_MODE 0b01000000
#define DISPLAY_OFF 0b10101110
#define DISPLAY_ON 0b10101111
#define NORMAL_DISPLAY 0b10100110
#define REVERSE_DISPLAY 0b10100111
#define ENTIRE_DISPLAY_ON 0b10100101
#define ENTIRE_DISPLAY_OFF 0b10100100
#define SET_PAGE_ADDR_HEADER 0b10110000
#define SET_LOW_COL_ADDR_HEADER 0b00000000
#define SET_HIGH_COL_ADDR_HEADER 0b00010000
#define SET_DISPLAY_START_LINE 0b01000000
#define SET_CONSTRAST_CONTROL_MODE 0b10000001
#define SET_SEGMENT_REMAP 0b10100000
#define SET_MULTIPLEX_RATION 0b10101000

struct Oled
{
    I2C_TypeDef *hi2c;
    int addr;
};

void init_oled(struct Oled oled);
void oled_send_cmds(struct Oled oled, int lenght, int *commands);
void oled_entire_display_control(struct Oled oled, int is_on);
void oled_draw_line(struct Oled oled, int line_nb);
void oled_clear_display(struct Oled oled);
void oled_draw_char(struct Oled oled, char ch, int line, int col);
void oled_draw_string(struct Oled oled, char* chs, int line, int col);
