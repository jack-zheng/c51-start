#include <REGX52.H>

// 管脚定义
sbit LCD_RS=P2^7;
sbit LCD_RW=P2^6;
sbit LCD_EN=P2^5;

#define LCD_DATA_POART P0

/**
	* @brief 1ms延时，为了方便移植，没有重用类库
  * @param 无
  * @retval 无
  */
void Delay()		//@12.000MHz 1ms
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief 写一位指令
  * @param 指令
  * @retval 无
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DATA_POART=Command;
	LCD_EN=1;
	Delay();	// 时序上时间足够，实际上不行，可能时字模转化需要事件
	LCD_EN=0;
	Delay();
}

/**
  * @brief 写一位数据
  * @param 数据
  * @retval 无
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DATA_POART=Data;
	LCD_EN=1;
	Delay();	// 时序上时间足够，实际上不行，可能时字模转化需要事件
	LCD_EN=0;
	Delay();
}

/**
  * @brief 初始化，设置显示模式
  * @param 无
  * @retval 无
  */
void LCD_Init()
{
	LCD_WriteCommand(0x01);	// 清屏，光标复位
	LCD_WriteCommand(0x06);	// 读写后 AC+1，画面不动
	LCD_WriteCommand(0x0C); // 显示开，光标关，闪烁关
	LCD_WriteCommand(0x38); // 两排显示，8位数据接口
}

/**
  * @brief 移动光标
	* @param Line 行号 1-2
	* @param Column 列 1-16
  * @retval 无
  */
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if(Line==1)
	{
		// LCD_WriteCommand(0x80|Column-1); 视频教程用了|但是语义上用+也是一样的，文档里面用的就是+
		LCD_WriteCommand(0x80+Column-1);
	} else if (Line==2)
	{
		LCD_WriteCommand(0x80+(Column-1+0x40));
	}
}

/**
  * @brief 写一个字符
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param Char 要显示的字符
  * @retval 无
  */
void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

/**
  * @brief 写一个字符串
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param String 要显示的字符串
  * @retval 无
  */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief 返回值=X的Y次方
  */
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief 显示给定数字
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param Number 要显示的数字
	* @param Length 数字长度
  * @retval 无
  */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10); // 写数据的时候要做偏移量转化
	}
}

/**
  * @brief 显示给定有符号数字
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param Number 要显示的有符号数字
	* @param Length 数字长度
  * @retval 无
  */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Num;
	LCD_SetCursor(Line, Column);
	
	if(Number>0)
	{
		LCD_WriteData('+');
		Num=Number;
	} else {
		LCD_WriteData('-');
		Num=-Number;	// 当Number为-32768时，Number=-Number 转化会失败，所以声明一个无符号int做转换
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Num/LCD_Pow(10,i-1)%10); // 写数据的时候要做偏移量转化
	}
}

/**
  * @brief 16进制显示给定数字
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param Number 要显示的数字
	* @param Length 数字长度
  * @retval 无
  */
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i,HexNum;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		HexNum=Number/LCD_Pow(16,i-1)%16;
		if(HexNum<10)
		{
			LCD_WriteData('0'+HexNum);
		} else {
			LCD_WriteData('A'+HexNum-10);
		}
	}
}

/**
  * @brief 2进制显示给定数字
	* @param Line 行号 1-2
	* @param Column 列 1-16
	* @param Number 要显示的数字
	* @param Length 数字长度 1-16
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}