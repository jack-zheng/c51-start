#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

int result;

void main()
{
	LCD_Init();
//	LCD_ShowChar(1,1,'A');
//	LCD_ShowString(1,3,"HELLO");
//	LCD_ShowNum(1,9,123,3);
//	LCD_ShowSignedNum(1,13,-66,2);
//	LCD_ShowHexNum(2,1,0xA8,2);
//	LCD_ShowBinNum(2,4,0xAA,8);
	while(1)
	{
		LCD_ShowNum(1,1,result,3);
		Delaynms(1000);
		result+=1;
	}
}