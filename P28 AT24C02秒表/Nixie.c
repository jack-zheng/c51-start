#include <REGX52.H>

sbit DATA=P0^2; // 穿行数据输入口
sbit SHCP=P0^4; // 移位控制, 当信号从0变为1时，数据移动一位
sbit STCP=P2^3; // 并行输出控制位

// 数码管显示区								0		1			2		3			4		5		  6		7			8		9		灭		-
code unsigned char Nixie[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf}; 
// 位选区
code unsigned char Position[]={0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; 
// 数码管显示缓存区，main 中通过改变他来指定每个数码管的显示内容
unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10};

/**
  * @brief 改变 Nixie_Buf 的值，间接改变扫描显示的值
  * @param Location：位置，1-8；Number：段码表 Nixie 的范围
  * @retval 无
  */
void Nixie_SetBuf(unsigned char Location, Number)
{
	Nixie_Buf[Location]=Number;
}

/**
  * @brief 八位数码管显示
	* @param pos: 位选信号,取值范围1-8，e.g. 1选中最左边的数码管
	*					val: 需要显示的数值
  * @retval 
  */
void Nixie_Scan(unsigned char pos, unsigned char val)
{
	unsigned char seg=Nixie[val];
	unsigned char i,position=Position[pos];
	SHCP=0;
	STCP=0;
	// 先将要显示的8位数据移入寄存器
	for(i=0; i<8; i++)
	{
		if(seg & 0x80)
		{
			DATA=1;
		}else{
			DATA=0;
		}
		// 0->1 移位数据
		SHCP=1;
		SHCP=0;
		// 这里时按照以前视频的习惯写的，如果按照最新的习惯应该时再上面通过 0x80>>i 操作数据
		seg<<=1;
	}
	// process position next
	for(i=0; i<8; i++)
	{
		if(position & 0x80)
		{
			DATA=1;
		}else{
			DATA=0;
		}
		// change TTL to move data
		SHCP=1;
		SHCP=0;
		// data move left
		position<<=1;
	}
	// 松开闸门，将串行数据并行输出
	STCP=1;
}

/**
  * @brief 定时器监听程序，每隔20ms检测按键状态
  * @param 无
  * @retval 无
  */
void Nixie_Loop()
{
	static unsigned char i=0;
	Nixie_Scan(i, Nixie_Buf[i]);
	i++;
	if(i>=9){i=0;}
}