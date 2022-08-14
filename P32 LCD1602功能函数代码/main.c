#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(1,9,69,2);
	LCD_ShowSignedNum(1,12,-68,2);
	LCD_ShowHexNum(2,1,0x08,2);
	LCD_ShowBinNum(2,4,0xcc,8);
	LCD_ShowChar(2,13,0xDF);
	LCD_ShowChar(2,14,'C');
	LCD_ShowString(1,16,"Welcome to China!");
	while(1)
	{
		LCD_WriteCommand(0x18); // 移动字幕效果
		Delay(1000);
	}
}