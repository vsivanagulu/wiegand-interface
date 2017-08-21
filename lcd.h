#ifndef LCD_LPC2148
#define	LCD_LPC2148
#define LCDRS (1<<24)
#define LCDRW (1<<23)
#define LCDEN (1<<22)
#define LCD_MASK (0x0F<<10)
#define CMD    0x01
#define DAT    0x00
#define LCD_BUSY_FLAG      (1 << 13)
#define FIRST_LINE_POS0 0X80
#define SECOND_LINE_POS0 0XC0
#define CLEAR 0X01

void Delays(unsigned int dly);
void wait_lcd(void);
void lcd_write(unsigned char val,unsigned char cmd);
void lcd_data(unsigned char dt);
void lcd_str(char *p);
void lcd_cmd(unsigned char command);
void init_lcd(void);
#endif  
