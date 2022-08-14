#include <REGX52.H>

void Timer0_Init()		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;	// 打开 Timer0 中断开关
	EA = 1;		// 打开中断总开关
	PT0 = 0;	// 设置 Timer0 优先级位低
}

/* 1s 定时器模板
void Timer0_Rountine() interrupt 1
{
	// 中断计数器
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		// 重置计数器
		T0Count=0;
		// TODO
	}
}
*/