# c51-start

Notebook of learning c51 mcu

## Env Setup

1. download keil
1. I use usb to give board power so need to install CH340 driver, but it failed, seems not compatible with win10, and I use [CH341Ser](http://www.wch.cn/download/CH341SER_EXE.html) instead
1. STC-ISP software download, [Link here](http://www.stcisp.com/stcisp620_off.html)

### Hello world sample - turn on led

```c
#include<reg52.h>
// P1 stand for 8 IO ports
sbit led1 = P1^0;
void main()
{
    led1 = 0;
    while(1)
    {
    }
}
```

PS: this setup cost me about 2 hours...
