#include <REGX52.H>

//引脚定义
sbit OneWire_DQ=P3^7;

/**
  * @brief  单总线初始化
  * @param  无
  * @retval 从机响应位，0为响应，1为未响应
  */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ=1; // 将 OneWire 总线拉高，准备进行初始化
	OneWire_DQ=0; //将 OneWire 总线拉低，发送初始化信号。
	i = 227;while (--i);		//Delay 500us 初始化：主机将总线拉低至少480us，然后释放总线，等待15~60us后，存在的从机会拉低总线60~240us以响应主机，之后从机将释放总线

	OneWire_DQ=1;
	i = 29;while (--i);			//Delay 70us
	AckBit=OneWire_DQ;
	i = 227;while (--i);		//Delay 500us
	return AckBit;
}

/**
  * @brief  单总线发送一位
  * @param  Bit 要发送的位
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ=0;
	i = 2;while (--i);			//Delay 10us
	OneWire_DQ=Bit;
	i = 22;while (--i);			//Delay 50us
	OneWire_DQ=1;
}

/**
  * @brief  单总线接收一位
  * @param  无
  * @retval 读取的位
   *发送一位：主机将总线拉低60~120us，然后释放总线，表示发送0；主机将总线拉低1~15us，
		然后释放总线，表示发送1。从机将在总线拉低30us后（典型值）读取电平，整个时间片应大于60us
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ=0;
	i = 1;while (--i);			//Delay 5us
	OneWire_DQ=1;
	i = 1;while (--i);			//Delay 5us
	Bit=OneWire_DQ;
	i = 22;while (--i);			//Delay 50us
	return Bit;
}

/**
  * @brief  单总线发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  单总线接收一个字节
  * @param  无
  * @retval 接收的一个字节
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}
