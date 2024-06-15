#include <REGX52.H>
#include "OneWire.h"

//DS18B20指令
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE

/**
  * @brief  DS18B20开始温度变换
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT()
{
	OneWire_Init(); // 初始化 OneWire 总线，OneWire 是一种串行通信协议
	OneWire_SendByte(DS18B20_SKIP_ROM);// 发送跳过 ROM 命令，用于单一设备的情况
	OneWire_SendByte(DS18B20_CONVERT_T);// 发送温度转换命令
}

/**
  * @brief  DS18B20读取温度
  * @param  无
  * @retval 温度数值
  */
float DS18B20_ReadT()
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();//读取温度的低字节。
	TMSB=OneWire_ReceiveByte();//读取温度的高字节。
	Temp=(TMSB<<8)|TLSB;
		Temp&=0xfffffffc;
	T=Temp/16.0;//// 将温度值除以16，得到实际的温度值（DS18B20以0.0625度为单位）DS18B20的温度精度是12位，即它可以测量温度的范围被分为4096个等分，每个等分代表0.0625度。因此，实际的温度值需要通过除以16来转换为以摄氏度为单位的浮点数值。
	return T;
}
