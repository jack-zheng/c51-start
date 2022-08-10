#include "OneWire.h"
#include "LCD1602.h"

#define DS18B20_SKIP_ROM				0xCC
#define DS18B20_CONVERT_T				0x44
#define DS18B20_READ_SCRATCHPAD	0xBE

/**
  * @brief 发送温度转化命令
  * @param 无
  * @retval 无
  */
void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
  * @brief 读取温度
  * @param 无
  * @retval 温度
  */
float DS18B20_ReadTemp()
{
	unsigned char TLSB, TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	// 接收16位温度数据，并整合
	TLSB=OneWire_ReadByte();
	TMSB=OneWire_ReadByte();
	Temp=(TMSB<<8)|TLSB;
	// LCD_ShowBinNum(1,1,Temp,16);// 显示二进制数做对比
	// 转化位浮点型便于计算
	T=Temp/16.0;
	return T;
}