/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  timer.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/28
*��  ��:  Timerģ�����ͷ�ļ�
*��  ע:  ������HRSDK-GDB-8P506
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô���
          �������ķ��ջ������е��κη������Ρ�
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
