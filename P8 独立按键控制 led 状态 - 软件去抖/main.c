#include <REGX52.H>

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delaynms(unsigned int nms)
{
	while(nms)
	{
		Delay1ms();
		nms--;
	}
}

/**
* left  P1.0
* up	  P1.1
* down  P1.2
* right P1.3
*
* led 	P1.7
* 轻触按键按下时会有 5-10 ms 的抖动
*/
void main()
{
	while(1)
	{
		if(P1_2==0)
		{
			Delaynms(20);
			while(P1_2==0);
			Delaynms(20);
			P1_7=~P1_7;
		}
	}
}