#ifndef __DS1302_H__
#define __DS1302_H__

// 时间数组，和芯片中的时间寄存器相对应，分别为
// 年，月，日，时，分，秒，每周第n天
extern unsigned char DS1302_Time[];

void DS1302_Init();
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_WriteByte(unsigned char Command, Data);
void DS1302_GetTime();
void DS1302_SetTime();

#endif