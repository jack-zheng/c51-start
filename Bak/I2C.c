#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  * @brief 在SCL位高电平的时候，SDA由高变低，开始通信
  * @param 无
  * @retval 无
  */
void I2C_Start()
{
	I2C_SDA=1; // 拉高SDA，前提准备，不然如果原来就是0，直接拉低没用
	I2C_SCL=1;
	
	I2C_SDA=0;	// SDA由高变低，开始通信
	I2C_SCL=0; 	// 开始通信后，SCL也拉低，完成准备工作
}

/**
  * @brief 在SCL位高电平的时候，SDA由低变高，结束通信
  * @param 无
  * @retval 无
  */
void I2C_Stop()
{
	I2C_SDA=0; // 拉低SDA做准备
	I2C_SCL=1;
	
	I2C_SDA=1;
}

/**
  * @brief 发送给从机数据之后，读取从机应答
  * @param 无
  * @retval 从机应答
  */
unsigned char I2C_ReceiveAck()
{
	unsigned char Data=0x00;
	I2C_SDA=1;	// 释放数据线，等待应答
	I2C_SCL=1;	// 按协议，拉高SCL之后，数据不再变化
	Data=I2C_SDA;
	I2C_SCL=0;
	return Data;
}

/**
  * @brief 接收完从机数据后，给从机发送反馈
  * @param AckBit 应答位，0应答，1非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  * @brief 接收从机数据
  * @param 无
  * @retval 接收的数据
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char Data=0x00,i;
	I2C_SDA=1;	// 释放SDA，回到高阻态，等待从机响应
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;	// SCL上拉，开始读数
		if(I2C_SDA){ Data|=(0x80>>i);}
		I2C_SCL=0;	// SCL下拉，从机输出数据
	}
	
	return Data;
}

/**
  * @brief 发送数据给从机
  * @param Byte 要发送的数据
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}