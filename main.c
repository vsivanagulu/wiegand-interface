#include<LPC214x.h>
#include"lcd.h"
#include"weigand.h"

char count = 0;

extern volatile char data[40] ;
extern volatile char weigandsize;
extern volatile char dataready;


int main(void)
{
	
	int id= 0;
	init_lcd();


 	lcd_cmd(FIRST_LINE_POS0);
	lcd_str("Hello Easy ARM ");
	lcd_cmd(SECOND_LINE_POS0);
	lcd_str("Welcome LCD");
	weigand_init();
	
	
	while(1)
	{
		
		if(dataready)
		{
			 char j;
			 lcd_cmd(0x01);
			 count = (count+1)%10;
			 lcd_data(0x30+count);
			 lcd_data(':');
			 lcd_data(' ');
 	  		 
			 if(weigandsize ==26)
			 {
					id =0;
					for(j=9;j<=24;j++)
					{

					id =   (id<<1) |   (data[j]-'0'); 	

					}
					lcd_data(0x30+(id/10000));
					lcd_data(0x30+((id/1000)%10));
					lcd_data(0x30+((id/100)%10));
					lcd_data(0x30+((id/10)%10));
				    lcd_data(0x30+(id%10));


 			 } 
			 else if(weigandsize == 37)
			 {
					id =0;
					for(j=17;j<=35;j++)
					{

					id =   (id<<1) |   (data[j]-'0'); 	

					}
					lcd_data(0x30+(id/10000));
					lcd_data(0x30+((id/1000)%10));
					lcd_data(0x30+((id/100)%10));
					lcd_data(0x30+((id/10)%10));
				    lcd_data(0x30+(id%10));
 

			 }
			 dataready = 0;
			 weigandsize = 0;			 

		}


	}
	
}
