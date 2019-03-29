/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  
*��  ע:  ������HRSDK-GDB-HR8P506 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "lib_config.h"
#include "lib_uart.h"
#include "system_hr8p506.h"

#define RW_BUFF_SIZE    64

typedef union{
	uint8_t RecBuff[RW_BUFF_SIZE];
	struct{
		uint8_t deviceAddr;
		uint8_t funcCode;
		uint8_t RecBuffLen;
		uint8_t Rsvd[20];
	}item;
}RxFrameDef;
extern RxFrameDef rxFrame;

typedef union {
	uint8_t SendBuff[RW_BUFF_SIZE];
	struct {
		uint8_t deviceAddr;
		uint8_t funcCode;
		uint8_t RecBuffLen;
		uint8_t rsvd[10];
	}item;
}TxFrameDef;
extern TxFrameDef txFrame;


#define MAXSIZE 256
typedef struct{
	uint16_t chsum;
  uint8_t ch[MAXSIZE];
  uint8_t len;
}StringType;
extern StringType String;

typedef union{
	struct {
		uint8_t RecStart:1;
		uint8_t RecMsg:1;
		uint8_t Send:1;
		uint8_t RecBuffLen;
		uint8_t SendBuffLen;
		uint8_t rsvd[10];
		uint8_t Err;
	}Flag;
	
}AfterStageType;
extern AfterStageType AfterStage;


#define USART_GETFLAGSTATUSTOTAL       600000

uint8_t strAssign(StringType *String,uint8_t *chars);
void UART0Init(void);
void UART1Init(void);

#endif
