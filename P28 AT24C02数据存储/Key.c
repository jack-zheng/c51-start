#include <REGX52.H>
#include <Delay.H>

/**
	* @brief 返回独立键盘按键值，左，上，下，右分别返回1，2，3，4
  * @param 无
  * @retval 键位值
  */
unsigned char Key()
{
	if(P1_0==0)
	{
		Delay(20);
		while(P1_0==0);
		Delay(20);
		return 1;
	}
	
	if(P1_1==0)
	{
		Delay(20);
		while(P1_1==0);
		Delay(20);
		return 2;
	} 
	
	if(P1_2==0)
	{
		Delay(20);
		while(P1_2==0);
		Delay(20);
		return 3;
	} 
	
	if(P1_3==0)
	{
		Delay(20);
		while(P1_3==0);
		Delay(20);
		return 4;
	}
	
	return 0;
}


