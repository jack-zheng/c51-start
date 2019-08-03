/*=======================================================
<<<<<<<<<<<<<<<<<<< 爱普雷德技术团队 >>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<< 我们一起追求卓越 >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
旗舰网店: http://aplid.taobao.com/
官方邮箱: njaplid@163.com
 技术QQ1: 535676091
 技术QQ2: 1915624375
 技术QQ3: 154211813
---------------------------------------------------------
               All right reserved.2013.01
---------------------------------------------------------
 文件名: DS18B20.c
 描述: DS18B20采集温度并显示到数码管（12M晶振下操作）
 作者:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include <reg52.h>
#include <intrins.h>    // 因为此文件中用到了延时函数_nop_()，所以要包含_nop_()的头文件

/* 定义DS18B20接口对应的端口 */
//sbit DS18B20_DQ = P1^4; // DS18B20的数据通信引脚DQ
sbit DQ = P1^4;

/* 定义数码管显示模块接口对应的端口 */
sbit DIG_DATA = P0^2;   // 74HC595的数据输入引脚
sbit DIG_SHCP = P0^4;   // 74HC595的移位脉冲引脚
sbit DIG_STCP = P2^3;   // 74HC595的锁存脉冲引脚

/* 变量定义 */
unsigned char DigBuf[4];    //定义数码管显示缓冲区

code unsigned char Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // 数字段码，Segment[0]~Segment[9]分别对应数字0~9的段码
code unsigned char Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};       // 位选，Select[0]为全选，Select[1]~Select[8]分别对应第1位（最右侧）~第8位（最左侧）

/*---------------------------------------------------------------------------------------------------------*/
/* 温度模块DS18B20相关函数 */
/**********************************************
功能：
    延时函数
输入参数：
    n: 延时时长
输出参数：
    无
返回值：
**********************************************/
void Delay(unsigned int n)
{
    unsigned int i;
    while(n--)
    {
        i=200;
        while(i--);
    }
}
/*延时基准3us 晶振为11.0592MHz*/
void DelayXus(unsigned char n)
{
    while(n--);
}

void delay4us(unsigned char t){
	while(t--);
}
/**********************************************
功能：
    初始化DS18B20
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
 /*初始化序列：目的是看一下DS18B20是否存在，存在返回1，不存在则返回0。好进行下一步操作*/
void DS18B20Init(void)
{
	// master send a pull down to bus, bus low minimus time is 480 us.
	DQ = 0;
	delay4us(130);
	// then master release bus and wait for slave fead back
	DQ = 1;	
	// after bus released, 18b20 wait 15-60us and give a low signal, 
	delay4us(40);
	// this signal will last about 60-240us, then device release bus
    /* For this practice, ew just think this device would be work, so just delay time and let it go*/
	delay4us(100);
}

/**********************************************
功能：
    写一个字节到DS18B20
输入参数：
    WByte:要写的字节
输出参数：
    无
返回值：
**********************************************/
/*写DS18B20一个字节Byte*/
void DS18B20WriteOneByte(unsigned char cmd)
{
	unsigned char i;

	for (i=0;i<8;i++){
		if (cmd & 0x01){
			// if the bit 0 is high, generate high signal
			// to generate 1 time slot, pull down bus, and release in 15us, all write time slot must be a minimum 60us duration 
			DQ = 0;
			DQ = 1;
			delay4us(30);
		}else{
		 	// to generate 0 time slot, pull down bus and hold at least 60us
			/*hold low for more than 480us will cause all components on bus reset*/
			DQ = 0;
			delay4us(20);
			DQ = 1;	
		}
		cmd >>= 1;
	}	
}
/**********************************************
功能：
    从DS18B20读取一个字节
输入参数：
    无
输出参数：
    无
返回值：
    RecByte:从DS18B20所读取的字节
**********************************************/
unsigned char DS18B20ReadOneByte(void)
{
	unsigned char dat;
	// all read time slots must be a mininum of 60us in duration with a minimum of 1us recovery time between slots
	unsigned char i;
	for (i=0;i<8;i++){
		// DS18b20 transmit 1 by leave bus to high, and 0 by pull down bus to low till the time slot end.
		dat >>= 1;
		DQ = 0; // bus low as initiates
		DQ = 1;	// reset port and wait for receive
		// data from 18b20 valid for 15us after master's read signal, which mean, *master should finish sample in 15us!*
		if (DQ){
			// if DQ is high, give a 1 to dat
			dat |= 0x80;
		}
		delay4us(30);
	}
	return dat;
}
/**********************************************
功能：
    开始温度转换
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DS18B20TConvertStart(void)
{
    DS18B20Init();              //DS18B20初始化
    Delay(1);                   //延时
    
    DS18B20WriteOneByte(0xCC);     //发送跳过ROM指令
    DS18B20WriteOneByte(0x44);     //发送启动温度转换指令
}

/**********************************************
功能：
    获取温度值
输入参数：
    无
输出参数：
    Temperature: 温度值，16位数。
    其中BIT15——BIT11(符号位);
        BIT10——BIT4 (整数位);
        BIT3 ——BIT0 (小数位);
返回值：
**********************************************/
unsigned int DS18B20TGet(void)
{
    unsigned int Temperature;
    
    DS18B20Init();              //DS18B20初始化
    Delay(1);                   //延时
    
    DS18B20WriteOneByte(0xCC);     //发送跳过ROM指令
    DS18B20WriteOneByte(0xBE);     //发送读取便签指令
    
    Temperature = DS18B20ReadOneByte();    //读取便签的低字节（8位）
    Temperature |= DS18B20ReadOneByte()<<8;//读取便签的高字节（8位）
    
    return(Temperature);        //返回读取的便签值（16位）
}

/*---------------------------------------------------------------------------------------------------------*/
/* 数码管显示相关函数 */
/**********************************************
功能：
    输出位选字节和段码字节
输入参数：
    SelectByte:  位选字节
    SegmentByte: 段码字节
输出参数：
    无
返回值：
**********************************************/
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte)
{
    unsigned char i;
    
	DIG_SHCP = 0;   // 74HC595的移位脉冲引脚输出低电平
	DIG_STCP = 0;   // 74HC595的锁存脉冲引脚输出低电平
    
    /* 将段码字节（共8位，高位在前）移入74HC595芯片 */
	for(i=0; i<8; i++)
	{
        /* 判断数据的最高位，如果最高位是1，数据引脚输出高电平；如果是0，输出低电平 */
	    if(SegmentByte&0x80)
        {
	        DIG_DATA = 1;
        }
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
        /* 输出74HC595芯片的数据移位脉冲，每输出一个移位脉冲，74HC595内部的数据移动一位 */
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
        /* 要输出的数据左移一位，即为下一位数据的输出作准备 */
		SegmentByte <<= 1;
	}
    /* 将位选字节（共8位，高位在前）移入74HC595芯片 */
	for(i=0; i<8; i++)
	{
	    if(SelectByte&0x80)
        {
	        DIG_DATA = 1;
        }    
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
		SelectByte <<= 1;
	}
    /* 输出74HC595芯片的数据锁存脉冲，即将74HC595芯片接收到的最新数据输出到芯片的所有数据引脚 */
	DIG_STCP = 1;
	_nop_();
	DIG_STCP = 0;
	_nop_();
}

/**********************************************
功能：
    在某位显示自定义段码
输入参数：
    DigSelect: 数码管位选择（1——8，即最右到最左）
    CustomSeg: 自定义段码值
输出参数：
    无
返回值：
**********************************************/
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg)
{
    if(0<DigSelect<9)   //判断位选的值是否为1——8，若超出这个范围，则不作任何操作
    {
        DigOutput(Select[DigSelect],CustomSeg);
    }
}

/**********************************************
功能：
    在某位显示数字
输入参数：
    DigSelect: 数码管位选择（1——8，即最右到最左）
    Number:    数字（0——9）
    Dp:        小数点（1:显示；0:不显示）
输出参数：
    无
返回值：
**********************************************/
void DigShowNumber(unsigned char DigSelect, unsigned char Number, bit Dp)
{
    if((0<DigSelect<9)&&(Number<10))    //同时判断位选的值是否为1——8，显示值是否为0——9。若超出范围，则不作任何操作
    {
        if(Dp)
    	{
            DigOutput(Select[DigSelect],(Segment[Number]&~0x80));   //点亮小数点
    	}
    	else
    	{
            DigOutput(Select[DigSelect],(Segment[Number]|0x80));    //熄灭小数点
    	}
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/**********************************************
    主函数，读取并显示DS18B20的温度
**********************************************/
void main()
{
    unsigned int i=0;   //定义循环的计数值并赋初始值
    float TGet;         //定义从DS18B20读取的数
    signed int TShow;   //定义转换后需要显示的数
    
    while(1)
    {
        /* 步骤1：若满足判断语句，则启动温度转换 */
        if(i==0)
        {
            DS18B20TConvertStart();     //启动温度转换
        }
        /* 步骤2：若满足判断语句，读取温度值并转换存储至显示缓存 */
        if(i==100)
        {
            TGet = DS18B20TGet()*0.0625;//得到真实十进制温度值，因为DS18B20
        			                    //可以精确到0.0625度，所以读回数据的最低位代表的是0.0625度。
            TShow = TGet*10+0.5;        //放大十倍，这样做的目的将小数点后第一位也转换为可显示数字，同时进行一个四舍五入操作。

            if(TShow<0)                 //判断温度值是否为负数
            {
                DigBuf[0] = 0xbf;
                TShow = 0-TShow;
            }
            else
            {
                DigBuf[0] = TShow/1000; //保存温度百位值
            }
            TShow = TShow%1000;
            DigBuf[1] = TShow/100;      //保存温度十位值
            TShow = TShow%100;
            DigBuf[2] = TShow/10;       //保存温度个位值
            DigBuf[3] = TShow%10;       //保存小数点后一位值
        }
        /* 步骤3：对i进行加1或归零 */
        if(++i>3000)                    //将i的值加1并且判断i是否大于3000
        {
            i = 0;                      //若超出了3000，则归零
        }
        /* 步骤4：进行数码管的动态显示 */
        DigShowNumber(1,DigBuf[3],0);   //数码管第1位显示小数点后一位的值
        DigShowNumber(2,DigBuf[2],1);   //数码管第2位显示个位值，同时显示小数点
        DigShowNumber(3,DigBuf[1],0);   //数码管第3位显示十位值
        if(DigBuf[0]==0xbf)             //判断DigBuf[0]的值是否为0xbf，即判断温度是否为负数
        {
            DigShowCustom(4,0xbf);      //若是负数，第4位显示负号
        }
        else if(DigBuf[0]>0)            //若DigBuf[0]不为0xbf，再判断DigBuf[0]是否大于0
        {
            DigShowNumber(4,DigBuf[0],0);//若DigBuf[0]大于0，第4位显示该数值
        }
        else                            //否则
        {
            DigShowCustom(4,0xff);      //第4位数码管全灭
        }
    }
}