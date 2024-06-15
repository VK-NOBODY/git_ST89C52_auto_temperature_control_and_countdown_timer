#ifndef _XPT2046_H_
#define _XPT2046_H_


#define XPT2046_VBAT    0XAC
#define XPT2046_AUX     0XEC
#define XPT2046_XP      0X9C
#define XPT2046_YP      0XDC

unsigned int XPT2046_ReadAD(unsigned char Command);


#endif