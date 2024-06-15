#include <REGX52.H>

sbit XPT2046_DIN = P3^4;
sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DOUT = P3^7;

/**
  * @brief  ZPT2046读取AD值
  * @param  Command 命令字，范围：头文件内定义的宏，结尾的数字表示转换的位数
  * @retval AD转换后的数字量，范围：8位为0~255，12位为0~4095
  */

unsigned int XPT2046_ReadAD(unsigned char Command)
{
    unsigned int ADvalue = 0; // 存储读取到的模拟信号值
    unsigned char i;

    XPT2046_DCLK = 0;  // 下降沿开始传输数据
    XPT2046_CS = 0;    // 使能片选，开始数据传输

    // 发送命令
    for (i = 0; i < 8; i++)
    {
        XPT2046_DIN = Command & (0x80 >> i);  // 从命令的高位开始发送数据
        XPT2046_DCLK = 1;  // 上升沿时，数据被传输
        XPT2046_DCLK = 0;  // 下降沿准备下一个数据位
    }

    // 读取模拟信号
    for (i = 0; i < 16; i++)
    {
        XPT2046_DCLK = 1;  // 上升沿
        XPT2046_DCLK = 0;  // 下降沿

        // 如果数据线为高电平，则将对应位置为1
        if (XPT2046_DOUT)
        {
            ADvalue |= 0x8000 >> i;
        }
    }

    XPT2046_CS = 1;  // 关闭片选，结束数据传输

    return ADvalue >> 8;  // 返回高8位的模拟信号值
}

