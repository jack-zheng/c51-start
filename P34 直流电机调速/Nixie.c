#include <REGX52.H>

sbit DATA=P0^2; // bit data input
sbit SHCP=P0^4; // shift bit, 0->1, data move
sbit STCP=P2^3; // lock register control bit

code unsigned char Nixie[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

void SegmentDisplay(unsigned char pos, unsigned char val)
{
	unsigned char seg= Nixie[val];
	unsigned char i;
	SHCP=0;
	STCP=0;
	// according to the schematic diagram, segment val is before position select
	// so we process segment first
	for(i=0; i<8; i++)
	{
		if(seg & 0x80)
		{
			DATA=1;
		}else{
			DATA=0;
		}
		// change TTL to move data
		SHCP=1;
		SHCP=0;
		// data move left
		seg<<=1;
	}
	// process position next
	for(i=0; i<8; i++)
	{
		if(pos & 0x80)
		{
			DATA=1;
		}else{
			DATA=0;
		}
		// change TTL to move data
		SHCP=1;
		SHCP=0;
		// data move left
		pos<<=1;
	}
	// set STCP to 1, output the value
	STCP=1;
}