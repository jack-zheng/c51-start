#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"

float T;

void main()
{
	DS18B20_ConvertT(); // 程序开始时先 Convert 覆盖默认的85度
	Delay(1000);	// 以前的 Delay 定义都有问题，都写成 unsigned char 型了，怪不得定时不准...
	
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	
	while(1)
	{
		DS18B20_ConvertT();	// 转化温度
		T=DS18B20_ReadTemp();	// 读取温度
		// 显示温度
		if(T<0)
		{
			LCD_ShowChar(2,1,'-');
			T=-T;
		} else {
			LCD_ShowChar(2,1,'+');
		}
		LCD_ShowNum(2,2,T,3);	// 整数部分
		LCD_ShowChar(2,5,'.');
		LCD_ShowNum(2,6,((unsigned long)(T*10000))%10000,4);	// 小数部分
	}
}

