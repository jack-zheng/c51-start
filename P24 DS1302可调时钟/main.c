#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

// MODE=0,时间显示模式；MODE=1，时间设置模式
// 当前选中的修改位置
unsigned char KeyNum,MODE,TimeSelect,TimeSelectFlash; 

void ShowTimeMode()
{
	DS1302_GetTime();	// 将DS1302中存储的时间存入数组

	LCD_ShowNum(1,1,DS1302_Time[0],2); // 显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2); // 显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2); // 显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2); // 显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2); // 显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2); // 显示秒
}

void SetTimeMode()
{
	// 如果按下2，改变当前选中的改变位置
	if(KeyNum==2)
	{
		TimeSelect++;
		TimeSelect%=6;
	}
	
	// 如果按下3，选中位置数值+1
	if(KeyNum==3)
	{
		DS1302_Time[TimeSelect]++;

		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}
		// 日复位，如果是大月，超过31复位
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		} else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11) { // 如果是小月，超过30复位
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		} else {	// 如果是二月，再深入判断
			if(DS1302_Time[0]%4==0) // 如果是闰年，超过29归0
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			} else {	// 否则，超过28归0
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	
	// 如果按下4，选中位置数值-1
	if(KeyNum==4)
	{
		DS1302_Time[TimeSelect]--;

		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}
		// 日复位，如果是大月，超过31复位
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		} else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11) { // 如果是小月，超过30复位
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		} else {	// 如果是二月，再深入判断
			if(DS1302_Time[0]%4==0) // 如果是闰年，超过29归0
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			} else {	// 否则，超过28归0
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	
	if(TimeSelect==0 && TimeSelectFlash){ LCD_ShowString(1,1,"  "); }
	else { LCD_ShowNum(1,1,DS1302_Time[0],2); } // 显示年
	
	if(TimeSelect==1 && TimeSelectFlash){ LCD_ShowString(1,4,"  "); }
	else { LCD_ShowNum(1,4,DS1302_Time[1],2); } // 显示月

	if(TimeSelect==2 && TimeSelectFlash){ LCD_ShowString(1,7,"  "); }
	else { LCD_ShowNum(1,7,DS1302_Time[2],2); } // 显示日

	if(TimeSelect==3 && TimeSelectFlash){ LCD_ShowString(2,1,"  "); }
	else { LCD_ShowNum(2,1,DS1302_Time[3],2); } // 显示时

	if(TimeSelect==4 && TimeSelectFlash){ LCD_ShowString(2,4,"  "); }
	else { LCD_ShowNum(2,4,DS1302_Time[4],2); } // 显示分

	if(TimeSelect==5 && TimeSelectFlash){ LCD_ShowString(2,7,"  "); }
	else { LCD_ShowNum(2,7,DS1302_Time[5],2); } // 显示秒
	
	LCD_ShowNum(2,10,TimeSelect,2);
	LCD_ShowNum(2,13,TimeSelectFlash,2);
}

void main()
{
	LCD_Init();
	Timer0Init();
	DS1302_Init();
	
	DS1302_SetTime(); // 设置初始时间
	LCD_ShowString(1,1,"  -  -");// 设置时间之间的横线
	LCD_ShowString(2,1,"  :  x");
	
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)	// 按键1按下，改变模式
		{
			if(MODE==0){ MODE=1; TimeSelect=0;}	// 重置时间选择位
			else if(MODE==1){ MODE=0; DS1302_SetTime(); }	// 保存时间
		}
		
		// 更加 MODE 值进入显示/设置时间界面
		switch(MODE)
		{
			case 0: ShowTimeMode(); break;
			case 1: SetTimeMode(); break;
		}
	}
}

/**
  * @brief 设置时间时，每0.5s选中位闪烁 flag
  * @param 无
  * @retval 无
  */
void Timer0_Rountine() interrupt 1
{
	// 中断计数器
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		// 重置计数器
		T0Count=0;
		TimeSelectFlash=!TimeSelectFlash;
	}
}