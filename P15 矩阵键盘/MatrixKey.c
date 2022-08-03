#include <REGX52.H>
#include "Delay.h"

unsigned char MatrixKey()
{
	unsigned char tmp = 0;
//	P1=0xFF;
//	P1_0=0;
	P1=0xFE;
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); tmp = 1; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); tmp = 2; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); tmp = 3; }
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); tmp = 4; }
	
//	P1=0xFF;
//	P1_1=0;
	P1=0xFD;
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); tmp = 5; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); tmp = 6; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); tmp = 7; }
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); tmp = 8; }
	
//	P1=0xFF;
//	P1_2=0;
	P1=0xFB;
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); tmp = 9; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); tmp = 10; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); tmp = 11; }
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); tmp = 12; }
	
//	P1=0xFF;
//	P1_3=0;
	P1=0xF7;
	if(P1_4==0) { Delay(20); while(P1_4==0); Delay(20); tmp = 13; }
	if(P1_5==0) { Delay(20); while(P1_5==0); Delay(20); tmp = 14; }
	if(P1_6==0) { Delay(20); while(P1_6==0); Delay(20); tmp = 15; }
	if(P1_7==0) { Delay(20); while(P1_7==0); Delay(20); tmp = 16; }
	
	return tmp;
}
