#include <REGX52.H>

void Timer0_Init()
{
    TMOD = TMOD & 0xF0; // 清零TMOD的低四位，确保定时器0工作在方式0
    TMOD = TMOD | 0x01; // 设置TMOD的低四位为0001，表示定时器0工作在方式1（16位定时器）
    TH0 = 0x4C;         // 设置定时器0的初始值的高8位
    TL0 = 0x00;         // 设置定时器0的初始值的低8位
    TF0 = 0;            // 定时器中断标志位清零
    TR0 = 1;            // 启动定时器0，开始计数
    ET0 = 1;            // 允许定时器0中断
    EA = 1;             // 允许总中断
    PT0 = 0;            // 定时器0中断的优先级设为低优先级
}


void Timer0_SetCounter(unsigned int val)
{
    TH0 = val/256;
    TL0 = val%256;
}


unsigned int Timer0_GetCounter(void)
{
    return (TH0<<8)|TL0;
}

void Timer0_Run(unsigned char flag)
{
    TR0 = flag;
}


