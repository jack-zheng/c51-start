#include <REGX52.H>

sbit DS1302_CLK =P3^6;	
sbit DS1302_IO  =P2^1;
sbit DS1302_CE  =P3^7;	// Chip Enable 片选位，置1后可对芯片进行设置

#define DS1302_SEC	0x80
#define DS1302_MIN	0x82
#define DS1302_HOUR	0x84
#define DS1302_DATE	0x86
#define DS1302_MON	0x88
#define DS1302_DAY	0x8A
#define DS1302_YEAR	0x8C
#define DS1302_WP		0x8E

// 时间数组，和芯片中的时间寄存器相对应，分别为
// 年，月，日，时，分，秒，每周第n天
char DS1302_Time[]={99, 11, 28, 23, 59, 55, 6};

/**
  * @brief 初始化 DS1302，片选置0，时钟拉低
  * @param 无
  * @retval 无
  */
void DS1302_Init()
{
	DS1302_CE	=0;
	DS1302_CLK=0;
}

/**
	* @brief 读取DS1302数据，传入命令地址，返回 RTC 芯片返回对应的8位结果
  * @param DS1302_xxx 命令字/地址
  * @retval 8位结果
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	
	Command|=0x01;	// 使用统一的 DS1302_xxx 作为命令字/地址，写地址最后一位或 1 可以得到读地址
	
	DS1302_CE=1;
	
	// 指定读地址，这里的时钟信号设定还是很巧妙的
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_CLK=0;
		DS1302_CLK=1;
	}
	
	// 读取寄存器数据
	for(i=0;i<8;i++)
	{
		DS1302_CLK=1;
		DS1302_CLK=0;
		if(DS1302_IO)
		{
			Data|=(0x01<<i);
		}
	}
	
	// 关闭片选
	DS1302_CE=0;
	// DS1302_IO=0; // 视频教程中读取完后IO置0，不然数据会出问题，我本地倒没这种情况
	return Data;
}

/**
  * @brief 写入DS1302数据
  * @param DS1302_xxx 命令字/地址
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command, Data)
{
	unsigned char i;
	
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_CLK=1;
		DS1302_CLK=0;
	}
	
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_CLK=1;
		DS1302_CLK=0;
	}
	
	DS1302_CE=0;
}

/*** 
* 
  * @brief 将时间数组中设定的时间存入 DS1302 中。
	*					时间转化算法 BCD=DEC/10*16 + DEC%16
  * @param 无
  * @retval 无
  */
void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP, 0x00);	// 解除写保护状态
	DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MON,	DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE, DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,	DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MIN,	DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SEC,	DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,	DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP, 0x80);	// 恢复写保护状态
}

/**
	* @brief 将DS1302的时间显示在 LCD 上
	*					时间转化算法 DEC=BCD/16*10 + BCD%16;
  * @param 无
  * @retval 无
  */
void DS1302_GetTime()
{
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MON);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MIN);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SEC);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}