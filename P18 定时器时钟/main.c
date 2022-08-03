#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"

unsigned char Hor=23,Min=59,Sec=55;

void main()
{
	LCD_Init();
	Timer0Init();
	// 预期时间格式 HH:MM:SS
	LCD_ShowChar(1, 3, ':');
	LCD_ShowChar(1, 6, ':');
	// 显示时间
	// Q: while 刷屏会不会影响屏幕寿命？
	while(1)
	{
		LCD_ShowNum(1, 1, Hor, 2);
		LCD_ShowNum(1, 4, Min, 2);
		LCD_ShowNum(1, 7, Sec, 2);
	}
}

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
		Sec++;
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hor++;
				if(Hor>=24)
				{
					Hor=0;
				}
			}
		}
	}
}