#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	LCD_ShowNum(2, 1, 0, 4);
	
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)
		{
			// 只允许输入 4 位密码
			if(Count<4)
			{
				// 每输入一位数，password 进位并加上输入的数
				Password*=10;
				Password+=KeyNum;
				Count++;
			}
			LCD_ShowNum(2, 1, Password, 4);
			
			if(KeyNum==10)
			{
				// 检测密码
				if(Password==2345)
				{
					LCD_ShowString(1,14,"OK ");
				} else {
					LCD_ShowString(1,14,"ERR");
				}
				// 检测完后重置标志位, 并清空输入显示
				Password=0;
				Count=0;
				LCD_ShowNum(2, 1, 0, 4);
			}
			
			// 如果是按下取消键，重置标志位, 并清空输入显示
			if(KeyNum==11)
			{
				Password=0;
				Count=0;
				LCD_ShowNum(2, 1, 0, 4);
			}
		}
		
	}
}