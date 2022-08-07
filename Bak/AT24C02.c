#include <REGX52.H>
#include <I2C.h>

#define AT24C02_DEVICE 0xA2	// 开发板地址线是 001，并没有全部接地

void AT24C02_WriteByte(unsigned char WordAddress, Data)
{
	unsigned char Ack;
	I2C_Start();
	I2C_SendByte(AT24C02_DEVICE);
	Ack=I2C_ReceiveAck();
	if(Ack==0){P1=0xf0;}
//	I2C_SendByte(WordAddress);
//	Ack=I2C_ReceiveAck();
//	if(Ack==0){P1_1=0;}
//	I2C_SendByte(Data);
//	Ack=I2C_ReceiveAck();
//	if(Ack==0){P1_2=0;}
//	I2C_Stop();
}

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