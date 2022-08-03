#include <INTRINS.H>

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void Delay(unsigned char nms)
{
	while(nms--)
	{
		Delay1ms();
	}
}
