#include <REGX52.H>

/**
	* @brief 串口通信初始化，支持中断
  * @param NA
  * @retval NA
  */
void UART_Init()		//4800bps@11.0592MHz
{
	// 设置串口
	PCON &= 0x7F;	// 波特率不倍速, 
	SCON = 0x50;	// 8位数据,可变波特率,允许接收数据
	
	// 设置 T1 定时器
	TMOD &= 0x0F;	// 清除定时器1模式位
	TMOD |= 0x20;	// 设定定时器1为8位自动重装方式
	TL1 = 0xFA;		// TimerLow  设定定时初值
	TH1 = 0xFA;		// TimerHigh 设定定时器重装值
	TR1 = 1;			// TimerRun1 启动定时器1
	
	EA = 1;				// EnableAll 开启中断总开关
	ES = 1;				// EnableSerial 开启串口中断开关
}

/**
  * @brief 通过串口发送一个字节
  * @param 发送的字节信息
  * @retval NA
  */
void UART_Send(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);	// 等待发送完成，硬件置位完成标志位
	TI=0;					// 软件复位标志位
}

/* 中断模板
void UART_Routine() interrupt 4
{
	if(RI==1)					// 理论上这个判断可以省略的样子
	{
		// TODO
		RI=0;						// ReceiverInterrupt 软件复位中断标志位
	}
}
*/