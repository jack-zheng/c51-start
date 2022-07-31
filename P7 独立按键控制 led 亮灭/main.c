#include <REGX52.H>

/**
* left  P1.0
* up	  P1.1
* down  P1.2
* right P1.3
*
* led 	P1.7
*/
void main()
{
	while(1)
	{
		if(P1_2==0 && P1_1==0)
		{
			// if down pushed, light the led
			P1_7 = 0;
		} else {
			// turn off led
			P1_7 = 1;
		}
	}
}