# c51-start

Notebook of learning c51 mcu

* (B站学习视频)[https://www.bilibili.com/video/BV1Mb411e7re?spm_id_from=333.999.0.0]

## Env Setup

学习视频简介中作者给出了 baidu 网盘，里面又 Keil 和 STC 的软件，可以直接安装。其中涉及到关闭 Windows 防火墙的步骤，不关闭的话，License 注册软件不能打开，过程可以参考这篇(博客)[https://blog.csdn.net/Mirecz/article/details/108961731]

## 示例程序

### P4 点亮 led

1. 在目标位置新建文件夹, 命名位 '01 点亮 led'
2. 打开 keil, 选择 Project -> New uVersion Project -> 选择新建的文件夹 -> 文件名设为 Project -> 确定
3. 此时会弹出选择芯片的弹框， STC 系列不在列表中，选择同型号的 Atmel 89c52 代替即可。弹出 copy 启动文件选项，选否即可
4. 展开目录树中 Target 1，在 Source Group 1 上右键选择 'Add new item to ...', 再选中 C File，输入文件名 main 创建主文件
5. 在 main 中写入逻辑代码(右键可以直接插入头文件，很方便)
6. 在 Build 按钮的同一行，有一个 Options for target 按钮(看上去像魔术棒) 点击，选择 Output 选项卡，勾选 'Create HEX File' 用来生成烧录文件
7. 点击 Build 按钮，生成文件，看控制台输出，显示生成位置在目标文件夹的 Objects 下
8. 打开 STC-ISP 软件，选择单片机型号 'STC89C52RC/LE52RC'
9. 选择串口号，一般会自动适配
10. 点击 打开程序文件，选择生成的 .hex 文件
11. 点击 下载/编程 按钮，同时给开发板上电，软件右下侧会显示烧录状态

```c
#include <REGX52.H>

void main() 
{
	P1=0x55; //1111 1110
	while(1)
	{
	}
}
```

### P5 led 闪烁

过程和前面一样，这里额外介绍了一下 STC-ISP 软件的软件延时代码功能。

打开 STC，软件右侧有很多实用工具，其中一个是 软件延时计算器，根据开发板具体配置，选择 系统频率，指令集等参数，然后 CV 即可, 一秒延时示例代码如下

PS: 指令集那边选仔细了，不然结果会出问题，STC89C52RC 是在 STC-Y1 这个系列里的

```c
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

```

需要注意的是，他在实现中调用了 `_nop_()` 方法，要使用这个还需要在引入另外一个头文件 `#include <INTRINS.H>`

### P6 led 流水灯

这节主要的点是函数封装，没什么难度

```c
#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delaynms(unsigned int nms)
{
	while(nms)
	{
		Delay1ms();
		nms--;
	}
}

void main()
{
	P1=0xFE; //1111 1110
	Delaynms(500);
	P1=0xFD; //1111 1101
	Delaynms(500);
	P1=0xFB; //1111 1011
	Delaynms(500);
	P1=0xF7; //1111 0111
	Delaynms(500);
	P1=0xEF; //1110 1111
	Delaynms(500);
	P1=0xDF; //1101 1111
	Delaynms(500);
	P1=0xBF; //1011 1111
	Delaynms(500);
	P1=0x7F; //0111 1111
	Delaynms(500);
}
```

### P7 独立按键控制 led 亮灭

新增内容为通过读取按键状态控制灯状态

```c
#include <REGX52.H>

/**
* left  P1.0
* up	P1.1
* down  P1.2
* right P1.3
*
* led 	P1.7
*/
void main()
{
	while(1)
	{
		if(P1_2==0 && P1_1==0)
		{
			// if down pushed, light the led
			P1_7 = 0;
		} else {
			// turn off led
			P1_7 = 1;
		}
	}
}
```

### P8 独立按键控制 led 状态

增加了按键去抖效果

```c
/**
* left  P1.0
* up	P1.1
* down  P1.2
* right P1.3
*
* led 	P1.7
* 轻触按键按下时会有 5-10ms 的抖动
*/
void main()
{
	while(1)
	{
		if(P1_2==0)
		{
			Delaynms(20);
			while(P1_2==0);
			Delaynms(20);
			P1_7=~P1_7;
		}
	}
}
```

### P9 独立按键控制 led 显示二进制

声明一个 unsigned char LedNum=0 表示状态，按键按下时赋值给 P1 端口并取反达到效果，可惜我的开发板按键和 led 用的同一个 P 口，无法实现这个实验了

### 12 动态数码管显示

* 74HC245, 数据缓冲器，由于课程中的数码管时共阴极的，正极如果都接 IO 口，由于单片机 IO 口电流很弱，所以添加了这个 245 芯片，用来增强电流的。类似驱动电机的时候需要驱动芯片，原理时一样的
* TM1640 两根线就能控制16位数码管，节省 IO
* 74HC595 通过 3 根数据线 + 2 根电源线就可以控制 8 个数码管。串转并操作。三根数据线分别是电平线，时钟移位线和数据输出控制线。

代码实现中声明代码段的时候用了 code 关键字，这种设置可以将定义放到 ROM 中，避免占用 RAM 空间，每次使用的时候都去 ROM 中读取

根据开发板的教学视频，基于 74HC595 实现了动态扫描，发现硬件 debug 的能力还是不行，需要多实践

### 回忆篇 - 一些常用元器件及其使用

1. Hello world sample - turn on led
    * this setup cost me about 2 hours...
1. Turn on/off relay
1. Bee
1. Button
    * when handle with button event, add delay to avoid shake.

#### 数码管

* 74HC595 用于扩展数码管
* pin9 级联输出
* A 数据输入位
* pin11 数据记录位，给一个高电平脉冲作为标记（0-1-0）
* pin12 数据输出位，一个高电平脉冲，引脚输出变为记录的样子

#### 矩阵键盘

过程比较长，并没有想象的简单，但是可以通过慢慢的迭代来完成这个功能，比如先点亮数码管，到数码管显示两位，再到数码管根据参数显示。。。最后再到键盘显示

#### 时钟芯片 DS1302

* C51单片机的语句运行时间是 us 级别的
* 通信规则：先发命令码，再读/写数据
* 命令码可以告诉芯片你想做什么
* 读出来的时间数值是十六进制的，比如读出来的秒位0x59 - 十进制显示为89, 需要在数码管显示的时候做下处理
* 在写之前记得关闭写保护，你不能确定之前的程序有没有关闭，不然可能不能进行写的动作

#### AT24C02 断电保护

* data change only happened when SCL is low
* 数据读取的时候有四步，我一直以为只有三步的。。。
    + 输入操作 w
    + 输入地址
    + 输入操作 r
    + 读取返回值

#### PCF8591 实现AD/DA 转化

基本和上节内容一样，也是用了IIC协议，可以重用很多函数。 呼吸灯里面的实现算法还是很巧妙的。。。

#### 串口通信

1. 寄存器设置
1. 波特率设置， 9600。 选定 11.0592M 的晶振，刚好整除
1. 当数据接受完后， RI自动变1， 处理完后软件复位 0

很多概念还是很模糊，寄存器有哪些功能什么的，不过我还是打算先看下去，以后用需要的话再回头复习

#### LCD1602 显示

Busy Check 的时候很坑的一点， 当 E 从 0 变为 1 时, BF flag 才会填充到IO口。。。

#### 定时，中断

* STC-SPI 工具可以给出定时器的样码，简直骚操作 - 但是好像不怎么好使
* 16位定时器需要手动重置 TH0, TL0 的初始值
* MCU是单线程的。。。当进去EX0是其他中断是不运行的

#### 红外信号软件解码 - VS1838B

1. 引导码 + 用户码 + 数据码 + 数据反码 = 32 bit
1. 起始码: 9ms 高电平 + 4ms 低电平
1. 脉冲周期：1.125 - 0; 2.25 - 1
1. 式例程序写的太垃圾了，把波段时常统计为放到了中间做重置，我楞是没读懂他的代码，做了几个中断实验才看出来，Fuck Damn It!!!
1. 红外接收去收到的波形和遥控器发出来的刚好是反的，所以用下降沿触发的形式去检测刚好合适

#### LCD12864 display

* 驱动形式和LCD1602很像，只实现了最基本的功能，进阶版的功能以后有用再说。显示使用的北部芯片是ST7920
* 显示英文时，16x8, 中文 8x4
* 行地址,奇怪的设定，好像是为了图片实现才搞得这一套地址系统, 文档上给的第三四行地址还不对？擦擦擦
        + 1st 80H-8FH
        + 2nd 90H-9FH
        + 3rd 88H-AFH
        + 4th 98H-BFH
* 很棒的位图制作教程，不需要任何额外的工具 [How To](https://www.exploreembedded.com/wiki/Displaying_Images_and_Icons_on_GLCD),不过教程上有一点写错了，需要选择 Horizontal, 选 Vertical 会乱码的！！！软件名字 'LCDAssistant'

#### DS18B20

单总线通信，简直牛皮。51一个语句执行时间是多少？很神奇。

### 相关资料

74595 芯片阅读:

![functional diagrame](images/74595_functional_diagrame.png)

通过上面的功能图可以比较直观的理解74595的工作原理：

* 使用时通过 DS 引脚串行输入数据
* SHCP - shift register clock pin, 相当于一个开关，出发时数据进入
* STCP 相当于一个闸，开启后数据统一输出到 Qn pin 脚
* Q7S，相当于芯片扩容，一片只能存8位，两片的话可以扩展到16位

引脚说明图：

![pin](images/74HC595.png)
![desc](images/74595_desc.png)

### 创建自己的库文件

试着用网上的教程走了一遍，都没能成功，菜菜菜。。。有机会再试试把，浪费一晚上时间了

## 采坑实录

1. 习惯了 Java 语法，习惯性的没有把变量声明放到函数体第一排，排了半天的错，擦擦擦~

## TODO

1. 搜索一下怎么给C程序定制注释，让他看上去更专业
