/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  timer.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  Timer模块程序头文件
*备  注:  适用于HRSDK-GDB-8P506
          本软件仅供学习和演示使用，对用户直接引用代码
          所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__

#include "HR8P506.h"
#include "lib_config.h"
#include "system_hr8p506.h"

extern volatile uint32_t system1msTicker; 
extern volatile uint16_t systemSecTicker; 
extern volatile uint16_t system1secTicker;
#define  getAbsTickMs(ticker)   ((system1msTicker - ticker)&0x7fff)
#define MAX_TICK_PERIOD                 4320000    /* 12hour*3600s*1000ms */

void T16NxInit(void);

#endif
