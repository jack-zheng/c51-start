#include <REGX52.H>

code unsigned char Nixie[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

sbit DATA=P0^2; // bit data input
sbit SHCP=P0^4; // shift bit, 0->1, data move
sbit STCP=P2^3; // lock register control bit

void digOutput(unsigned char pos, unsigned char val)
{
	unsigned char i;
	SHCP=0;
	STCP=0;
	// according to the schematic diagram, segment val is before position select
	// so we process segment first
	for(i=0; i<8; i++)
	{
		if(val & 0x80)
		{
			DATA=1;
		}else{
			DATA=0;
		}
		// change TTL to move data
		SHCP=1;
		SHCP=0;
		// data move left
		val<<=1;
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

void main()
{
	while(1){
		digOutput(0x80, Nixie[1]);
		digOutput(0x40, Nixie[2]);
		digOutput(0x20, Nixie[3]);
		digOutput(0x10, Nixie[4]);
		digOutput(0x08, Nixie[5]);
		digOutput(0x04, Nixie[6]);
		digOutput(0x02, Nixie[7]);
		digOutput(0x01, Nixie[8]);
	}
}