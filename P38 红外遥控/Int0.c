#include <REGX52.H>

/**
  * @brief 中断初始化
  * @param 无
  * @retval 无
  */
void Int0_Init(void)
{
	IT0=1;	// 外部中断0类型设置，1为下降沿触发，0为低电平触发
	IE0=0;	// 中断标志位清0，貌似可以不做，是硬件置位的
	EX0=1;	// 外部中断使能
	EA=1;		// 中断总开关打开
	PX0=1;	// 优先级设置
}

/* 中断模板
void Int0_Rountine() interrupt 0
{
	Num++;
}
*/