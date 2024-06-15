#ifndef _TIMER0_H_
#define _TIMER0_H_

void Timer0_Init();
void Timer0_SetCounter(unsigned int val);
unsigned int Timer0_GetCounter(void);
void Timer0_Run(unsigned char flag);


#endif