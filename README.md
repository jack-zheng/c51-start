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
1. 数码管
    * 74HC595 用于扩展数码管
    * pin9 级联输出
    * A 数据输入位
    * pin11 数据记录位，给一个高电平脉冲作为标记（0-1-0）
    * pin12 数据输出位，一个高电平脉冲，引脚输出变为记录的样子 

### 相关资料

74595 引脚及说明:

![pin](images/74HC595.png)
![desc](images/74595_desc.png)
