#include <REGX52.H>

void Delay(unsigned char nms)		//@12.000MHz
{
	unsigned char i, j;
	
	while(nms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}
