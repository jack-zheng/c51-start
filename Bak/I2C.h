#ifndef __LCD1602_H__
#define __LCD1602_H__

void I2C_Stop();
void I2C_Start();
unsigned char I2C_ReceiveAck();
unsigned char I2C_ReceiveByte(void);
void I2C_SendByte(unsigned char Byte);
void I2C_SendAck(unsigned char AckBit);

#endif
