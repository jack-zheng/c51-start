#ifndef __OneWire_H__
#define __OneWire_H__

unsigned char OneWire_Init(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReadByte(void);

#endif