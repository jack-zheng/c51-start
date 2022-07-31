#include <REGX52.H>
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

void Delaynms(unsigned int nms)
{
	while(nms)
	{
		Delay1ms();
		nms--;
	}
}

void main()
{
	P1=0xFE; //1111 1110
	Delaynms(500);
	P1=0xFD; //1111 1101
	Delaynms(500);
	P1=0xFB; //1111 1011
	Delaynms(500);
	P1=0xF7; //1111 0111
	Delaynms(500);
	P1=0xEF; //1110 1111
	Delaynms(500);
	P1=0xDF; //1101 1111
	Delaynms(500);
	P1=0xBF; //1011 1111
	Delaynms(500);
	P1=0x7F; //0111 1111
	Delaynms(500);
}