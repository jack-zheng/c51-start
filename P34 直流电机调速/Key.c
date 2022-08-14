#include <REGX52.H>
#include <Delay.h>

unsigned char Key(void)
{
	unsigned char KeyNum=0;
	if(P1_0==0) {Delay(20); while(P1_0==0); Delay(20); KeyNum=1;}
	if(P1_1==0) {Delay(20); while(P1_1==0); Delay(20); KeyNum=2;}
	if(P1_2==0) {Delay(20); while(P1_2==0); Delay(20); KeyNum=3;}
	if(P1_3==0) {Delay(20); while(P1_3==0); Delay(20); KeyNum=4;}
	return KeyNum;
}