#include <REGX52.H>
#include "Timer0.h"
#include <INTRINS.H>

unsigned char KeyNum;

void main()
{
	//Timer0Init();
	// 设置 LED 初始状态
	P1=0xFE;

	while(1)
	{
		// 由于按键冲突，打算使用短路帽模拟按键
		// P2.0=1 使用导线接地模仿按键按下
		// 算了还是不好模拟，跳过，直接做始终吧
	}
}

/**
* 中断逻辑: 流水灯，频率位 1s
**/
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
		P1=_crol_(P1, 1);
	}
}



