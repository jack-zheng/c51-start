#include <REGX52.H>
#include <INTRINS.H>

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



void main()
{
	while(1)
	{
		P1=0xFE;
		Delay1000ms();
		P1=0xFF;
		Delay1000ms();
	}
}	