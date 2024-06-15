#include "UART.h"
#include "Timer0.h"
#include "XPT2046.h"
#include <stdio.h>
#include "Delay.h"
#include "MatrixKey.h"
#include "LCD1602.h"
#include "OneWire.h"
#include "DS18B20.h"
#include <stdlib.h>
#include "Nixie.h"
#include "reg52.h"
#include "public.h"
#include "smg.h"
#include "ired.h"
#include "Key.h"
#include "AT24C02.h"
#include "Nixie2.h"
#include "MatrixLED.h"
//定义直流电机控制管脚
sbit DC_Motor=P1^0;
#define DC_MOTOR_RUN_TIME	5000	
unsigned char KeyNum;
unsigned char Min,Sec,MiniSec;
unsigned char RunFlag=1;
int temp5 = 0;
int temp = 1;
int temp1 = 0;
static int temp2 = 0;
float T;
int num1,num2,num3,num4,num5,Offset;
u8 ired_buf[3];

sbit BEEP=P2^5;	//将P2.5管脚定义为BEEP


unsigned char code Animation[]={
0x00,0x00,0x7F,0x41,0x41,0x41,0x7F,0x00,
0x00,0x00,0x21,0x61,0x7F,0x01,0x01,0x00,
0x00,0x00,0x4F,0x49,0x49,0x49,0x79,0x00,
0x00,0x00,0x49,0x49,0x49,0x49,0x7F,0x00,
0x00,0x00,0x78,0x08,0x08,0x08,0x7F,0x00,
0x00,0x00,0x79,0x49,0x49,0x49,0x4F,0x00,
0x00,0x00,0x7F,0x49,0x49,0x49,0x4F,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x7F,0x00,
0x00,0x00,0x7F,0x49,0x49,0x49,0x7F,0x00,
0x00,0x00,0x79,0x49,0x49,0x49,0x7F,0x00,
0x21,0x7F,0x01,0x00,0x7F,0x41,0x41,0x7F,
0x21,0x7F,0x01,0x00,0x21,0x7F,0x01,0x00,
0x21,0x7F,0x01,0x00,0x4F,0x49,0x49,0x79,
0x21,0x7F,0x01,0x00,0x49,0x49,0x49,0x7F,
0x21,0x7F,0x01,0x00,0x78,0x08,0x08,0x7F,
0x21,0x7F,0x01,0x00,0x79,0x49,0x49,0x4F,
0x21,0x7F,0x01,0x00,0x7F,0x49,0x49,0x4F,
0x21,0x7F,0x01,0x01,0x40,0x40,0x40,0x7F,
0x21,0x7F,0x01,0x00,0x7F,0x49,0x49,0x7F,
0x21,0x7F,0x01,0x00,0x7F,0x49,0x49,0x7F,
0x4F,0x49,0x79,0x00,0x7F,0x41,0x41,0x7F,
0x4F,0x49,0x79,0x00,0x00,0x21,0x7F,0x01,
0x4F,0x49,0x79,0x00,0x4F,0x49,0x49,0x79,
0x4F,0x49,0x79,0x00,0x49,0x49,0x49,0x7F,
0x4F,0x49,0x79,0x00,0x78,0x08,0x08,0x7F,
0x4F,0x49,0x79,0x00,0x79,0x49,0x49,0x4F,
0x4F,0x49,0x79,0x00,0x7F,0x49,0x49,0x4F,
0x4F,0x49,0x79,0x00,0x7F,0x49,0x49,0x7F,
0x4F,0x49,0x79,0x00,0x79,0x49,0x49,0x7F,
0x49,0x49,0x7F,0x00,0x7F,0x41,0x41,0x7F

};
void Uart_SendDate(char  dat)
{
		ES = 0;  // 关闭串口中断，防止在发送过程中发生中断
    SBUF = dat; // 将要发送的数据放入串口发送缓冲寄存器
    while(TI!= 1); // 等待直到发送完毕，TI为发送中断标志位
    TI = 0; // 清除发送中断标志位
		ES = 1; // 打开串口中断
}
 
char putchar(char c)//将返回的数值打印到串口
{
    Uart_SendDate(c);// 调用Uart_SendDate函数发送字符
    return c; // 返回发送的字符，通过printf输出

}

void main()
{
 unsigned char i,Offset=0,Count=0;
	DC_Motor=0;//关闭电机
	LCD_Init(); //LCD初始化
	Delay(1000); //延迟等待初始化成功
	UART_Init(0xF4); //串口初始化
	Timer0_Init(); //定时器初始化
	ired_init();//红外初始化
	Timer0_Init();

	Sec=AT24C02_ReadByte(1);
	Sec=24;
	
	while(1)
	{		



        // 检测红外按键1是否按下 (假设红外按键1的码是0x3F39)
//        if (ired_buf[0] == 0x3F && ired_buf[1] == 0x39) {
//						temp  = 0;
//		        smg_display(ired_buf, 6);
//					
//        }
				
			KeyNum=Key();		//获取独立按键键码
			if(KeyNum)			//如果按键按下
			{
				if(KeyNum==1)	//如果K1按键按下
				{
					temp2 = 1;

				} else if(KeyNum == 2) {
					temp2 = 2;
				}
				else if(KeyNum == 3) {
					temp2 = 3;
				}
			}
			


		


		if(temp1 == 1) {

		


			//else if(P3^0==0)			//如果K1按键按下
//			{
//				Delay(20);		//延时消抖
//				while(P3^0==0);	//松手检测
//				Delay(20);		//延时消抖
//					KeyNum = 2;
//			} else if(P3^2==0)			//如果K1按键按下
//			{
//				Delay(20);		//延时消抖
//				while(P3^2==0);	//松手检测
//				Delay(20);		//延时消抖
//					KeyNum = 3;
//			} else {  //如果K1按键按下
//					KeyNum = 0;
//			} 



			if(temp2 == 1){
				LCD_ShowNum(1,1,Sec,3);
			}  
			else if(temp2 == 2) {
				
				while(temp2==2)	//如果K1按键按下
				{
					
					int intSec2 = (int)Sec;
					MatrixLED_Init();
					
					for(i=0;i<8;i++)	//循环8次，显示8列数据
					{
						MatrixLED_ShowColumn(i,Animation[i+ 8 * intSec2]);
					}
					Count++;			//计次延时
					if(Count>60)
					{
						Count=0;
						
					}
					KeyNum=Key();	
					if(KeyNum != 0) {
						temp2 = KeyNum;
						break;
					}
					
				}
			} 
			else if (temp2 != 3){
				Nixie(1,Sec/10);
				Nixie(2,Sec%10);
				
			}
			
		}
			
		
	}

}

void Sec_Loop(void)
{
	if(RunFlag)
	{
		MiniSec++;
		if(MiniSec>=24)
		{
			MiniSec=0;
			Sec--;
			if(Sec<=0)
			{
				Sec=24;
			}
		}
	}
	
}





void timer_rutine() interrupt 1
{ 
	static unsigned int cnt = 0;
	static unsigned int cnt2 = 0;
   static unsigned int count_delay = 0; // 新增延时计数变量
	
	//static unsigned int T0Count1,T0Count2,T0Count3;
	TL0 = 0x18;		//设置定时初值   (65536 - 1000)%256  低八位
	TH0 = 0xFC;		//设置定时初值   (65536 - 1000)/256  高八位
			ired_buf[0]=gsmg_code[gired_data[2]/16];//将控制码高4位转换为数码管段码
		ired_buf[1]=gsmg_code[gired_data[2]%16];//将控制码低4位转换为数码管段码
		ired_buf[2]=0X76;//显示H的段码
	cnt++;
	cnt2++;
	if(cnt  > 10)
	{
//		float vol,NTC,GR;
			DS18B20_ConvertT();	//转换温度
			T=DS18B20_ReadT();	//读取温度	
			if(temp2 == 3 && cnt2 > 200) {
				int intSec = (int)Sec;
				if(temp5 != intSec) {
								printf("num:%d",intSec);
				} 
				temp5 = intSec;
					cnt2 = 0;
			}

			
			
		cnt = 0;
		

	}
	  count_delay++; // 增加延时计数
    if (count_delay >= 20) // 控制计数速度
    {		
				

        count_delay = 0;

        if (ired_buf[0] == 0x3f && ired_buf[1] == 0x39) { //1,0c
            temp1 = 0;
            temp = 1;
            if (T >= 28) {
                DC_Motor = 1; //开启电机
							BEEP=!BEEP;//产生一定频率的脉冲信号
            }
            else {
                DC_Motor = 0; //关闭电机
							BEEP=0;//关闭蜂鸣器
            }
        }

        if (ired_buf[0] == 0x06 && ired_buf[1] == 0x7f) { //2,18
            temp = 0;
            temp1 = 1;
            DC_Motor = 0; //关闭电机
						BEEP=0;//关闭蜂鸣器

            Sec_Loop();
        }

    }
		
				
			if(temp == 1) {
				num1 = T / 10;
				num2 = ((int)T) % 10;
				num3 = ((int)(T*10)) % 10;
				num4 = ((int)(T*100)) % 10;
				num5 = ((int)(T*1000)) % 10;		

				Nixie(1,num1);
				NixieWithDP(2,num2);
				Nixie(3,num3);
				Nixie(4,num4);
				Nixie(5,num5);
		}
		
		
		

}

void UART_Routine() interrupt 4
{
	//	static unsigned int cnt2 = 0;
	if(RI==1)					//如果接收标志位为1，接收到了数据
	{
		static int num=0;
		RI = 0; 
		num++;
	}

	//cnt2++;
//	if(cnt2 >= 1000) {

	//			cnt2 = 0;
//	}
	

}