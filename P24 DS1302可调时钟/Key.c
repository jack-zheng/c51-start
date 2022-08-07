#include <REGX52.H>

/**
  * @brief 延时 n ms
  * @param n 秒延时
  * @retval 无
  */
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
	} else if(P1_1==0)
	{
		Delay(20);
		while(P1_1==0);
		Delay(20);
		return 2;
	} else if(P1_2==0)
	{
		Delay(20);
		while(P1_2==0);
		Delay(20);
		return 3;
	} else if(P1_3==0)
	{
		Delay(20);
		while(P1_3==0);
		Delay(20);
		return 4;
	}
	
	return 0;
}


