#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "AT24C02.h"
#include "Delay.h"
#include "Key.h"

float T;
char TH,TL;	// Temp High & Temp Low
unsigned char KeyNum;

void main()
{
	Timer0_Init();	// 开启定时器
	DS18B20_ConvertT();	// 启动程序，先温度转化，覆盖默认值(85)
	Delay(1000);
	// 初始化温度显示
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	/* 初始化极值显示 */
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	// 先从EEPROM中读取极值
	TH=AT24C02_ReadByte(0);
	TL=AT24C02_ReadByte(1);
	// 如果极值非法，给默认值
	if(TH>125 || TL<-55 || TH<=TL) { TH=31; TL=25; }
	LCD_ShowSignedNum(2,4,TH,3);
	LCD_ShowSignedNum(2,12,TL,3);
	while(1)
	{
		/* 温度显示 */
		DS18B20_ConvertT();
		T=DS18B20_ReadTemp();
		if(T>0)
		{
			LCD_ShowChar(1,3,'+');
		} else {
			LCD_ShowChar(1,3,'-');
			T=-T;
		}
		LCD_ShowNum(1,4,T,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,((unsigned long)(T*100))%100,2);
		
		/* 阈值设置&显示 */
			KeyNum=Key();
			if(KeyNum)	// 只有按键按下的时候才刷新屏幕，节省时间
			{
				if(KeyNum==1) 
				{
					TH++;
					if(TH>=125)
					{
						TH=125;
					}
				}
				if(KeyNum==2)
				{
					TH--;
					if(TH<=TL){TH++;}
				}
				if(KeyNum==3)
				{
					TL++;
					if(TL>=TH){TL--;}
				}
				if(KeyNum==4)
				{
					TL--;
					if(TL<=-55)
					{
						TL=-55;
					}
				}
				LCD_ShowSignedNum(2,4,TH,3);
				LCD_ShowSignedNum(2,12,TL,3);
				
				/* 将改变后的极值存入 EEPROM */
				AT24C02_WriteByte(0,TH);
				Delay(5);
				AT24C02_WriteByte(1,TL);
				Delay(5);
			}
			
			// 如果当前温度大于设定的最值，显示报警信息
			if(T>TH)
			{
				LCD_ShowString(1,13,"OV:H");
			} else if(T<TL){
				LCD_ShowString(1,13,"OV:L");
			} else {
				LCD_ShowString(1,13,"    ");
			}
		}
}

void Timer0_Rountine() interrupt 1
{
	// 中断计数器
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	// 按键扫描间隔20ms
	if(T0Count>=20)
	{
		// 重置计数器
		T0Count=0;
		Key_Loop();
	}
}