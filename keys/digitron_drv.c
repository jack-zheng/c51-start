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
 文件名: digitron_drv.c
 描述: 数码管模块驱动c文件
 作者:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "digitron_drv.h"

code uint8 Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
code uint8 Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

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
static void DigOutput(uint8 SelectByte, uint8 SegmentByte)
{
    uint8 i;
    
	DIG_SHCP = 0;
	DIG_STCP = 0;

	for(i=0; i<8; i++)
	{
	    if(SegmentByte&0x80)
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
		SegmentByte <<= 1;
	}
	for(i=0; i<8; i++)
	{
	    if(SelectByte&0x80)
	        DIG_DATA = 1;
		else
		    DIG_DATA = 0;
		_nop_();
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
		SelectByte <<= 1;
	}
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
void DigShowCustom(uint8 DigSelect, uint8 CustomSeg)
{
    if(0<DigSelect<9)
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
void DigShowNumber(uint8 DigSelect, uint8 Number, bit Dp)
{
    if((0<DigSelect<9)&&(Number<10))
    {
        if(Dp)
    	{
            DigOutput(Select[DigSelect],(Segment[Number]&~0x80));
    	}
    	else
    	{
            DigOutput(Select[DigSelect],(Segment[Number]|0x80));
    	}
    }
}


/**********************************************
功能：
    初始化数码管，使数码管全灭
输入参数：
    无
输出参数：
    无
返回值：
**********************************************/
void DigInit(void)
{
    DIG_DATA = 0;
	DIG_SHCP = 0;
	DIG_STCP = 0;
    DigOutput(0x00,0xff);
}