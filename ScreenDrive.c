/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  
*��  ע:  ������HRSDK-GDB-HR8P506 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "ScreenDrive.h"

#define SystemFrequency 



void WrCmd(uint8_t Cmd)
{
    uint8_t data, i, CmdByte = 0x80;
     
    HT1621_SET_CS(0);
    for (i=0; i<4; i++)
    {
        if (CmdByte&0x80)
            HT1621_SET_DAT(1);
        else
            HT1621_SET_DAT(0);
        HT1621_SET_WR(0);
        Delay_us(4);
        HT1621_SET_WR(1);
        CmdByte <<= 1;
    }
     
    for (i=0; i<8; i++)
    {
        if (Cmd&0x80)
            HT1621_SET_DAT(1);
        else
            HT1621_SET_DAT(0);
        HT1621_SET_WR(0);
        Delay_us(4);
        HT1621_SET_WR(1);
        Delay_us(4);
        Cmd <<= 1;
    }
     
    HT1621_SET_CS(1);
}

void WrAddData(uint8_t Add, uint8_t Ddat)
{
    uint8_t i, CmdByte = 0xA0;
     
    //
    //led_disp_mem[Add] |= Ddat;
    //
 
    HT1621_SET_CS(0);
    for(i=0; i<3; i++)
    {
        if (CmdByte&0x80)
            HT1621_SET_DAT(1);
        else
            HT1621_SET_DAT(0);
        HT1621_SET_WR(0);
        Delay_us(4);
        HT1621_SET_WR(1);
        CmdByte <<= 1;        
    }
     
    Add <<= 2;
    for(i=0; i<6; i++)
    {
        if(Add&0x80)
            HT1621_SET_DAT(1);
        else
            HT1621_SET_DAT(0);
        HT1621_SET_WR(0);
        Delay_us(4);
        HT1621_SET_WR(1);
        Add <<= 1;
    }
     
    for(i=0; i<8; i++)
    {
        if (Ddat&0x80)
            HT1621_SET_DAT(1);
        else
            HT1621_SET_DAT(0);
        HT1621_SET_WR(0);
        Delay_us(4);
        HT1621_SET_WR(1);
        Ddat <<= 1;
    }
     
    HT1621_SET_CS(1);
}



