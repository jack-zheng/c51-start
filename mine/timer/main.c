#include <reg52.h>

/** 
* in this test, I will create a timer to finish 50ms delay 
* and in main function, flash the light with time gap 1s.
*/

void Timer0Init(void)		//50����@11.0592MHz
{
	TMOD = 0x01;
	TH0 = (65536 - 45872) / 256;	 // ��ʱ50ms  //����11.0592MHZ
	TL0 = (65536 - 45872) % 256;
	TH0 = 0x4C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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