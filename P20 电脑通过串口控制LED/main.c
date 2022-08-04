#include <REGX52.H>
#include "UART.h"

void main()
{
	UART_Init();
	while(1);
}

void UART_Routine() interrupt 4
{
	if(RI==1)					// 理论上这个判断可以省略的样子
	{
		P1=SBUF;				// 接收到的信息赋给 P1 口
		UART_Send(P1);	// 将接收到的值返回给 PC 端
		RI=0;						// ReceiverInterrupt 软件复位中断标志位
	}
}