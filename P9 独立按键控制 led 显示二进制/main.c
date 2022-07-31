#include <REGX52.H>

void Delayxms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;

	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

/*
* P1.0 left button
* P1.1 led1
* P1.1 led2
* P1.1 led3
* P1.1 led4
* P1.1 led5
* P1.1 led6
* P1.1 led7
* 
* button and led used same I/O unable to finish this project
*/
void main()
{
	unsigned char LedNum=1;
	while(1)
	{
		if(P1_0==0)
		{
			Delayxms(20);
			while(P1_0==0);
			Delayxms(20);
			
			LedNum++;
			P2=~LedNum;
		}
	}
}
