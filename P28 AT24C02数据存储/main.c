#include <REGX52.H>
#include <LCD1602.h>
#include <AT24C02.h>
#include <Delay.h>

unsigned char Data;

void main()
{
	LCD_Init();

	AT24C02_WriteByte(0,13);
	// 按照手册提示，写完之后需要等待5ms，等待数据存入芯片
	Delay(10);
	Data=AT24C02_ReadByte(0);
	LCD_ShowNum(2,1,Data,4);
//	
	while(1);
}