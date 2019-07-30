#include <reg52.h>

/**
* in this test, I will use interrupt to flash LED 2 per second
*/
unsigned char TIME_BASE;

void Init(void)
{
	TMOD = 0x01;
	TH0 = (65536 - 45872) / 256;	 // 定时50ms  //晶振：11.0592MHZ
	TL0 = (65536 - 45872) % 256;
	ET0 = 1;
	TR0 = 1;
	EA  = 1;
}


void Timer0_IRQ(void) interrupt 1
{
	TH0 = (655365 - 45872) / 256;
	TL0 = (655365 - 45872) % 256;
	/* 进入中断50ms +1次 */
	TIME_BASE++;
	
	if(TIME_BASE ==40)	 //	20ms * 50ms = 刚好等于1000ms 也就是1秒
	{
		TIME_BASE = 0;
		P1 = ~P1;
	}
}

void main(void){
	Init();
	while(1);
}