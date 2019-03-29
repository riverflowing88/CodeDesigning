/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  uart演示主程序头文件
*备  注:  适用于HRSDK-GDB-8P506
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "HR8P506.h"
#include "system_hr8p506.h"
#include "iic.h"
#include "spi.h"
#include "uart.h"
#include "GpioInit.h"
#include "systick.h"
#include "timer.h"
#include "Adc.h"
#include "sleep.h"
#include "crc.h"
#include "tm1621.h"




//uint8_t g_rxbuf=0x01;
#define RX0BUFSIZE  100
#define RX1BUFSIZE  100
extern uint8_t Rx1Buff[RX1BUFSIZE];   //????????
extern uint8_t Rx0Buff[RX0BUFSIZE];   //????????
extern uint8_t Rx1BuffLen;
extern uint8_t Rxd1Cnt;
extern uint8_t Rxd0Cnt;
extern __IO uint16_t SysErr;

extern uint8_t StartStr1[4];
extern uint8_t StopStr1[4];

//#define PIN1_H GPIO_WriteBit(GPIO_Pin_A9, 1); 
//#define PIN1_L GPIO_WriteBit(GPIO_Pin_A9, 0); 
//#define PIN2_H GPIO_WriteBit(GPIO_Pin_A8, 1); 
//#define PIN2_L GPIO_WriteBit(GPIO_Pin_A8, 0); 
//#define PIN3_H GPIO_WriteBit(GPIO_Pin_A7, 1); 
//#define PIN3_L GPIO_WriteBit(GPIO_Pin_A7, 0); 
//#define PIN4_H GPIO_WriteBit(GPIO_Pin_A6, 1); 
//#define PIN4_L GPIO_WriteBit(GPIO_Pin_A6, 0); 
//#define PIN5_H GPIO_WriteBit(GPIO_Pin_A5, 1); 
//#define PIN5_L GPIO_WriteBit(GPIO_Pin_A5, 0); 
//#define PIN6_H GPIO_WriteBit(GPIO_Pin_A4, 1); 
//#define PIN6_L GPIO_WriteBit(GPIO_Pin_A4, 0); 
//#define PIN7_H GPIO_WriteBit(GPIO_Pin_A3, 1); 
//#define PIN7_L GPIO_WriteBit(GPIO_Pin_A3, 0); 
//#define PIN8_H GPIO_WriteBit(GPIO_Pin_A2, 1); 
//#define PIN8_L GPIO_WriteBit(GPIO_Pin_A2, 0); 
//#define PIN9_H GPIO_WriteBit(GPIO_Pin_A1, 1); 
//#define PIN9_L GPIO_WriteBit(GPIO_Pin_A1, 0); 
//#define PIN10_H GPIO_WriteBit(GPIO_Pin_A0, 1); 
//#define PIN10_L GPIO_WriteBit(GPIO_Pin_A0, 0); 
//#define PIN19_H GPIO_WriteBit(GPIO_Pin_B1, 1); 
//#define PIN19_L GPIO_WriteBit(GPIO_Pin_B1, 0); 
//#define PIN18_H GPIO_WriteBit(GPIO_Pin_B0, 1); 
//#define PIN18_L GPIO_WriteBit(GPIO_Pin_B0, 0); 
//#define PIN17_H GPIO_WriteBit(GPIO_Pin_A31, 1); 
//#define PIN17_L GPIO_WriteBit(GPIO_Pin_A31, 0); 



#endif

