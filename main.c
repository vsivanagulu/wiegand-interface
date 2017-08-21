#include<LPC214x.h>
#include"lcd.h"
#include"weigand.h"

char count = 0;

extern volatile char data[40] ;
extern volatile char weigandsize;
extern volatile char dataready;


int main(void)
{
	
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

		     for(j=0;j<13;j++)
	   		{
				lcd_data(data[j]);
	   		}				
	  		 
			 if(weigandsize ==26)
			 {
				 lcd_cmd(0xc0);
				 for(j=13;j<weigandsize;j++)
		  		 {
					lcd_data(data[j]);
	
		  		 } 
			 } 
			 else if(weigandsize == 37)
			 {
				 lcd_cmd(0xc0);
				 for(j=13;j<29;j++)
		  		 {
					lcd_data(data[j]);
	
		  		 } 
				 Delays(10000);
				 lcd_cmd(0x01);
				 for(j=29;j<weigandsize;j++)
		  		 {
					lcd_data(data[j]);
	
		  		 }


			 }
			 dataready = 0;
			 weigandsize = 0;			 

		}


	}
	
}
