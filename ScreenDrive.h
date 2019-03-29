/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  uart.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  
*备  注:  适用于HRSDK-GDB-HR8P506 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __GPIO_INIT_H__
#define __GPIO_INIT_H__

#include "lib_config.h"
#include "lib_uart.h"
#include "system_hr8p506.h"
#include "systick.h"

void ScreenInit(void);
void SwitchInit(void);

#define MAIN_SW_H       GPIO_WriteBit(GPIO_Pin_A8, 1); 
#define MAIN_SW_L       GPIO_WriteBit(GPIO_Pin_A8, 0); 
//#define WR_H     GPIO_WriteBit(GPIO_Pin_A3, 1); 
//#define WR_L     GPIO_WriteBit(GPIO_Pin_A3, 0); 
//#define CS_H     GPIO_WriteBit(GPIO_Pin_A4, 1); 
//#define CS_L     GPIO_WriteBit(GPIO_Pin_A4, 0); 
//#define RD_H     GPIO_WriteBit(GPIO_Pin_A6, 1); 
//#define RD_L	   GPIO_WriteBit(GPIO_Pin_A6, 0); 

#define PIN_HT1621_CS           GPIO_Pin_A27 
#define PIN_HT1621_WR           GPIO_Pin_A3 
//#define PIN_HT1621_RD           GPIO_Pin_A6
#define PIN_HT1621_DAT          GPIO_Pin_A24
#define HT1621_SET_CS(value)    GPIO_WriteBit(PIN_HT1621_CS,value)
#define HT1621_SET_WR(value)    GPIO_WriteBit(PIN_HT1621_WR,value)
#define HT1621_SET_DAT(value)   GPIO_WriteBit(PIN_HT1621_DAT,value)
#define HT1621_READ_DAT         GPIO_ReadBit(PIN_HT1621_DAT)

//#define WR_H       GPIO_WriteBit(GPIO_Pin_A3, 1); 
//#define WR_L       GPIO_WriteBit(GPIO_Pin_A3, 0); 
//#define DATA_H     GPIO_WriteBit(GPIO_Pin_A24, 1); 
//#define DATA_L     GPIO_WriteBit(GPIO_Pin_A24, 0); 
//#define CS_H       GPIO_WriteBit(GPIO_Pin_A27, 1); 
//#define CS_L	     GPIO_WriteBit(GPIO_Pin_A27, 0); 

#endif
