#include <REGX52.H>
#include "UART.h"

/**
  *@brief UART initialization function:transmit data
  *@param No parameter
  *@retval None
  *@detail 
  */

void UART_Init(unsigned char c) //4800bps@11.0592MHz
{
	SCON=0x50; //允许串口接收数据，模式1
	PCON|=0x80; // 波特率加倍控制位设为1
	TMOD=TMOD&0x0F;// 清零TMOD寄存器的高四位，以确保定时器1的工作方式设置正确
	TMOD=TMOD|0x20;//
	TF1=0;	//定时器1溢出标志位清零，确保定时器起始状态为未溢出。			 
	TR1=1;//启动定时器		 
	TH1=c;////设置定时初始值
	TL1=c;//设置定时重载值
	ES=1;// 允许串口中断，启用串口中断允许位。
	EA=1;// 允许总中断，启用总中断允许位。
}


/**
  *@brief 
  *@param 
  *@retval 
  *@detail 
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);//
	TI=0;
}

/**
  *@brief 
  *@param
  *@param
  *@retval
  *@detail 
  */

//void UART_Routine() interrupt 4
//{
//	if(RI==1)
//	{
//		RI=0;
//	}
//}