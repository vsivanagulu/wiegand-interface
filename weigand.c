#include"weigand.h"

volatile char data[40]="****************************************" ;
volatile char weigandsize = 0;
volatile char dataready  = 0;


void weigand_init(void)
{

		initClocks();
		// selecting capture channels P0.30 and P0.4
		PINSEL1 |= (1<<28) |(1<<29) ;			// capture timers 0.0(bit 28,bit 29) 
		PINSEL0 |= (1<<9) ;						// 		 and 0.1(bit 9)
		dataready = 0;
		weigandsize = 0;
		initTimer1();
		initTimer0();



}


void initTimer0(void)
{
	T0CTCR|=0x1;			//Set counter Mode
	T0PR = 600-1; 	//Increment T0TC at every 600 clock cycles
										//600 clock cycles @60Mhz = 10 uS
	T0CCR = (1<<0) |  (1<<2) | (1<<3) | (1<<5) ;
 



	VICVectAddr4 = (unsigned )timer0ISR; //Pointer Interrupt Function (ISR)
	VICVectCntl4 = (1<<5) | 4; 	//(bit 5 = 1)->to enable Vectored IRQ slot
															//bit[4:0]) -> this the source number - here its timer0 which has VIC channel mask # as 4
	VICIntEnable = (1<<4);	// Enable timer0 interrupt
	
	T0TCR = (1<<1);				// Reset Timer
	T0TCR = (1<<0);				// start Timer
}

__irq void timer0ISR(void)
{
	long int readVal;
	readVal = T0IR; 		// Read current IR value	
//	IO0PIN ^= (1<<31); 	// Toggle LED at Pin P0.10
	
	if(0x10&readVal)
	{
	   // capture 0.0 d0 pin
		data[weigandsize++] = '0';
		resettimer1();

	}
	else if(0x20&readVal) 
	{
		  // capture 0.1 d1 pin
		  data[weigandsize++] = '1';
		  resettimer1();

	}
   else
   {}
   	
	T0IR = readVal; 		// Write back to IR to clear Interrupt Flag
	VICVectAddr = 0x0; 	// End of interrupt execution
}


void initTimer1(void)
{
	T1CTCR = 0x0;			//Set Timer Mode
	T1PR = 60000-1; 	//Increment T1TC at every 60000 clock cycles
										//60000 clock cycles @60Mhz = 1 mS
	
	T1MR0 = 100-1; 	//Zero Indexed Count-hence subtracting 1
	T1MCR = (1<<0) | (1<<1);//Set bit0 & bit1 to Interrupt & Reset TC on MR0  

	VICVectAddr5 = (unsigned )timer1ISR; //Pointer Interrupt Function (ISR)
	VICVectCntl5 = (1<<5) | 5; 	//(bit 5 = 1)->to enable Vectored IRQ slot
															//bit[4:0]) -> this the source number - here its timer0 which has VIC channel mask # as 5
	VICIntEnable = (1<<5);	// Enable timer0 interrupt
	
	T1TCR = (1<<1); 				// Reset Timer
}

__inline void stoptimer1(void)
{
	   T1TCR = (1<<1);	 // reset
	   T1TCR = 0; 		 //stop

}
 __inline void resettimer1(void)
{
	   T1TCR = (1<<1);	//reset
	   T1TCR = (1<<0);	// start
}

__irq void timer1ISR(void)
{
	long int readVal;
	readVal = T1IR; 		// Read current IR value	
 
 	dataready =1;

  	T1IR = readVal; 		// Write back to IR to clear Interrupt Flag

    stoptimer1();
	VICVectAddr = 0x0; 	// End of interrupt execution
}

void initClocks(void)
{
	PLL0CON = 0x01;   //Enable PLL
	PLL0CFG = 0x24;   //Multiplier and divider setup
	PLL0FEED = 0xAA;  //Feed sequence
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT & 0x00000400)); //is locked?
		
	PLL0CON = 0x03;  //Connect PLL after PLL is locked
	PLL0FEED = 0xAA; //Feed sequence
	PLL0FEED = 0x55;
	VPBDIV = 0x01;   // PCLK is same as CCLK i.e.60 MHz
}


