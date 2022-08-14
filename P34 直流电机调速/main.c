#include <REGX52.H>
#include <Key.h>
#include <Nixie.h>
#include <Timer0.h>

unsigned char KeyNum,Speed;
unsigned char Counter,Compare;
sbit LED=P1^7;

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();

		if(KeyNum==1)
		{
			Speed++;
			Speed%=4;
			if(Speed==0) {Compare=0;}
			if(Speed==1) {Compare=50;}
			if(Speed==2) {Compare=75;}
			if(Speed==3) {Compare=100;}
		}
		SegmentDisplay(1, Speed);
	}
}


void Timer0_Rountine() interrupt 1
{
	// 中断计数器
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;
	if(Counter>Compare)
	{
		LED=1;
	} else {
		LED=0;
	}
}
