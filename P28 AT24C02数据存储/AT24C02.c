#include <REGX52.H>
#include <I2C.h>

// 开发板地址线是 001，但是他的芯片是国产芯片，默认都是接的0，
// 直接自闭，debug了1小时，最后看十年前的开发板附送的例子才知道
#define AT24C02_DEVICE 0xA0	

/**
  * @brief 写入一个字节
  * @param WordAddress: 字地址
	* 				Data: 写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WordAddress, Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_DEVICE);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
  * @brief 读取一个字节
  * @param WordAddress: 字地址
  * @retval 字地址的值
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	// Dummy Write 虚拟写模式，指定要读取的字地址
	I2C_Start();
	I2C_SendByte(AT24C02_DEVICE);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	
	I2C_Start();	// 直接从 start 命令开始
	I2C_SendByte(AT24C02_DEVICE|0x01); // 修改最后一位1，READ模式
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}