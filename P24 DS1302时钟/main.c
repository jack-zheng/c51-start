#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

void main()
{
	LCD_Init();
	DS1302_Init();
	
	DS1302_SetTime(); // 设置初始时间
	LCD_ShowString(1,1,"  -  -");// 设置时间之间的横线
	LCD_ShowString(2,1,"  :  :");
	
	while(1)
	{
		DS1302_GetTime();	// 将DS1302中存储的时间存入数组

		LCD_ShowNum(1,1,DS1302_Time[0],2); // 显示年
		LCD_ShowNum(1,4,DS1302_Time[1],2); // 显示月
		LCD_ShowNum(1,7,DS1302_Time[2],2); // 显示日
		LCD_ShowNum(2,1,DS1302_Time[3],2); // 显示时
		LCD_ShowNum(2,4,DS1302_Time[4],2); // 显示分
		LCD_ShowNum(2,7,DS1302_Time[5],2); // 显示秒
	}
}