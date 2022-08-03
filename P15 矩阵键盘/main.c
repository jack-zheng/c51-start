#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Pushed Key:");
	
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)
		{
			LCD_ShowNum(2, 1, KeyNum, 2);
		}
		
	}
}