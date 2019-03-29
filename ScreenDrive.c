/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  uart.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  
*备  注:  适用于HRSDK-GDB-HR8P506 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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



