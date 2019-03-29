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
#ifndef __TM1621_H__
#define __TM1621_H__

#include "lib_config.h"
#include "lib_uart.h"
#include "system_hr8p506.h"
#include "systick.h"



#define RC_K                0x30
#define TIMEN               0x0C
#define SYSEN               0x02
#define SYSDIS              0x00
#define LCD_ON              0x06
#define LCD_OFF             0x04
#define BIAS1_2             0x50
#define BIAS1_3             0x52
#define AC                  0
#define DC                  1
#define Hz_50               1
#define Hz_60               0    

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
#define PIN_HT1621_B           GPIO_Pin_A16
#define PIN_HT1621_DAT          GPIO_Pin_A24
#define HT1621_SET_BACK(value)  GPIO_WriteBit(PIN_HT1621_B,value)
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
#define Error 0x08
#define USB   0x04
#define DC_B    0x02
#define S5    0x01

#define Charge    0x08
#define Light     0x04
#define AC_B        0x02

#define Freq_50    0x08
#define Freq_Hz    0x04
#define Freq_60    0x02

#define S4    0x08
#define S3    0x04
#define S2    0x02
#define S1    0x01

void TM1621Init(void);
void Writer_LCD(uint8_t COM1,uint8_t COM2,uint8_t COM3,uint8_t COM4);
void Writer_Voltage(float v_num);
void Writer_Watt(uint16_t num);
uint8_t Read_Dat(uint8_t r_addr);
void Write_Dat(uint8_t addr,uint8_t dat);
void Write_Cmd(uint8_t cmd);
uint8_t Read_TIMING(void);
void Write_TIMING(uint8_t dat, uint8_t num);


#endif
