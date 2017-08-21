#ifndef LPC2148_WEIGAND
#define LPC2148_WEIGAND

#include<LPC214x.h>

void weigand_init(void);

void initTimer0(void);
__irq void timer0ISR(void);
void initTimer1(void);
__inline void stoptimer1(void);
 __inline void resettimer1(void);
 __irq void timer1ISR(void);
 void initClocks(void);


#endif


 



 