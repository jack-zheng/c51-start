#include <reg52.h>

/** 
* in this test, I will create a timer to finish 50ms delay 
* and in main function, flash the light with time gap 1s.
*/

void Timer0Init(void)		//50毫秒@11.0592MHz
{
	TMOD = 0x01;
	TH0 = (65536 - 45872) / 256;	 // 定时50ms  //晶振：11.0592MHZ
	TL0 = (65536 - 45872) % 256;
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void main(void){
	unsigned char count=0;
	Timer0Init();
	P1 = 0x00; // init and turn on P1

	while(1){
		if(TF0 == 1){
			TF0 = 0; // reset flag
			count ++;
			if (count >= 14){
				count = 0; // reset counter
				P1 = ~P1; // nagtive P1 status
			}
		}
	}
		
}