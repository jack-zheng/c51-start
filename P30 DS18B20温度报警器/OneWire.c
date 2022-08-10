#include <REGX52.H>

sbit OneWire_DQ=P1^4;

/**
	* @brief 初始化，主机拉低一段时间(min: 480us, max: 960us)，释放总线(15-60us)，从机拉低作为响应(60-240us)
  * @param 无
  * @retval 从机响应: 0 有响应，1 无响应
  */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char Ack;
	EA=0;	// 关闭定时器，防止中断打乱总线时序
	OneWire_DQ=1;	// 准备工作，保证操作前DQ为高电平
	OneWire_DQ=0;	// 拉低电平开始通信
	i = 249;while (--i);	// 通过STC计算出的500us延时
	OneWire_DQ=1;	// 释放总线，延时60us等待电平自动上拉 + 10us 从机响应
	i = 32;while (--i);
	Ack=OneWire_DQ;	// 读取响应状态
	i = 249;while (--i);	// 延时500us跳过从机响应的剩余时间
	EA=1;
	return Ack; 
}

/**
  * @brief 主机下拉开始通信，从机采样窗口15-60us。一个写周期至少维持60us, 周期之间间隔至少1us.
  * @param 发送的电平状态
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA=0;	// 关闭定时器，防止中断打乱总线时序
	OneWire_DQ=0; // 开始通信
	i = 2;while (--i);// 维持5us,然后设置要发送的状态
	OneWire_DQ=Bit;
	i = 29;while (--i);// 延时60us等待从机采样结束
	OneWire_DQ=1;	// 结束后释放总线
	EA=1;
}

/**
	* @brief 主机下拉开始通信(不能长，1us就够了)，释放总线。主机在15-60us之间采样。一个写周期至少维持60us, 周期之间间隔至少1us.
  * @param 无
  * @retval 无
  */
unsigned char OneWire_ReadBit(void)
{
	unsigned char Bit,i;
	EA=0;	// 关闭定时器，防止中断打乱总线时序
	OneWire_DQ=0;	// 开始通信，执行一个语句已经达到1us的时限了
	OneWire_DQ=1;	// 释放总线
	i = 7;while (--i);	// 延时15us后开始采样
	Bit=OneWire_DQ;
	i = 22;while (--i);// 延时45us等待读周期完成
	OneWire_DQ=1;	// 结束后释放总线
	EA=1;
	return Bit;
}

/**
	* @brief 写字节(8bit), 低位先写
  * @param 写入的字节
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
	* @brief 读字节(8bit), 低位优先
  * @param 无
  * @retval 读取的字节
  */
unsigned char OneWire_ReadByte(void)
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++)
	{
//		Data|=OneWire_ReadBit()<<i;
		if(OneWire_ReadBit()){Byte|=0x01<<i;}
	}
	return Byte;
}