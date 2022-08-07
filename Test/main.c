#include <REGX52.H>
#include "Key.h"

unsigned char KeyNum, MODE;

void main()
{
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			MODE=KeyNum;
		}
		
		switch(MODE)
		{
			case 1: P1_4=~P1_4;break;
		}
	}
}