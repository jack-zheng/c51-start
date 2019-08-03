# c51-start

Notebook of learning c51 mcu

## Env Setup

1. download keil
1. I use usb to give board power so need to install CH340 driver, but it failed, seems not compatible with win10, and I use [CH341Ser](http://www.wch.cn/download/CH341SER_EXE.html) instead
1. STC-ISP software download, [Link here](http://www.stcisp.com/stcisp620_off.html)

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
