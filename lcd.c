#include<LPC214x.h>
#include"lcd.h"

 
void Delays(unsigned int dly)
{
	int i; 
	for(;dly>0;dly--)
	for(i=1200;i>0;i--);
}


void wait_lcd(void)
{
	 IO1CLR |= LCDRS;
	 IO1SET |= LCDRW|LCDEN;
	 while(IO1PIN & LCD_BUSY_FLAG);
	 IO1CLR |= LCDEN|LCDRW;
	 IO0DIR |= LCD_MASK;
}

void lcd_write(unsigned char val,unsigned char cmd)
{
	unsigned char temp;
	unsigned int temp1;
	if(cmd)
	{
	IO1CLR = LCDRS;  //Register Select is low
	}
	else
	{
	IO1SET = LCDRS; //Register Select is high
	}
	temp= val;                     //SENDING higher NIBBLE
	temp=(temp>>4)&0x0F;
	temp1=(temp<<10)&LCD_MASK;
	IO1SET |= LCDEN;  // lcd is enabled
	IO0CLR = LCD_MASK;
	IO0SET = temp1;
	Delays(50);
	IO1CLR |= LCDEN; //lcd is diabled
	temp = val;            // sending lower nibble
	temp&= 0x0F;
	temp1= (temp<<10)&LCD_MASK;
	Delays(50);
	IO1SET |= LCDEN; // lcd is enabled
	IO0CLR = LCD_MASK;
	IO0SET = temp1;
	Delays(50);
	IO1CLR |= LCDEN; //lcd is diabled	
	wait_lcd();		 
}		

void lcd_data(unsigned char dt)
{
  lcd_write(dt,DAT);	
}

void lcd_str(char *p)
{
	while(*p)
	{
		lcd_data(*p++);
	}
}

void lcd_cmd(unsigned char command)
{

 	lcd_write(command,CMD);


}


void init_lcd(void)
{
	IO1DIR |= 0x01c00000;
	IO1CLR |= 0x01c00000;
	IO0DIR |= 0x00003c00;
	Delays(500);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
	lcd_cmd(0x0c);
} 
