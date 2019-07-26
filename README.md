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

#### 时钟芯片 DS1302

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
