/********************************************************************************
  * @file    tm1621.c
  * @author  TenPao Software Team / Zotan
  * @version V1.0.0
  * @date    2019/03/14
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library.This file provides all the RCC firmware functions.
  * @note    Chip:TM1621/LQFP44
  * @history 1. <date> <author> <modification>
  *
  *          Copyright (C) 1979-2018 TenPao Ltd. All rights reserved.
  *******************************************************************************/

/* Includes --------------------------------------------------------------------*/
#include "main.h"

/* Variables -------------------------------------------------------------------*/

const uint8_t numble[10] = {0x5F, 0x06, 0x6B, 0x2F, 0x36, 0x3D, 0x7D, 0x07, 0x7F, 0x3F};

/* Function prototypes ---------------------------------------------------------*/

/**
  * @brief        TM1621初始化
  * @param        None
  * @retval       None
  * @note         None
  */

void TM1621Init(void)
{
  
    HT1621_SET_CS(1);
	HT1621_SET_WR(1);
//	GPIO_SetBits(GPIOA,GPIO_Pin_12);
    HT1621_SET_DAT(1);
	Write_Cmd(BIAS1_3);
	Write_Cmd(RC_K);
	Write_Cmd(LCD_ON);
	Write_Cmd(SYSEN);
    Write_Cmd(TIMEN);
	//Write_Dat_Bust(0,cmdat,16);
    
    Write_Dat(0x00, 0x01);
    Write_Dat(0x01, 0x00);
    Write_Dat(0x02, 0x04);
    Write_Dat(0x03, 0x00);
//    Write_Dat(0x04, 0x00);
//    Write_Dat(0x05, 0x00);
//    Write_Dat(0x06, 0x00);
//    Write_Dat(0x07, 0x00);
//    Write_Dat(0x08, 0x04);
//    Write_Dat(0x09, 0x08);
//    Write_Dat(0x0A, 0x00);
//    Write_Dat(0x0B, 0x00);
//    Write_Dat(0x0C, 0x00);
//    Write_Dat(0x0D, 0x00);
//    Write_Dat(0x0E, 0x00);
//    Write_Dat(0x0F, 0x00);
//    Write_Dat(0x10, 0x08);
//    Write_Dat(0x11, 0x04);
//    Write_Dat(0x12, 0x02);
//    Write_Dat(0x13, 0x01);

//    while(1)
//    {
//        Writer_Watt(199);
//        Writer_Voltage(90.5);
//        Writer_Power(25, AC);
//        Writer_frequency(Hz_60);
//        //regdata = Read_Dat(0x00);
//    }
    
}

void Write_TIMING(uint8_t dat, uint8_t num)
{
    static uint8_t byte = 0;
    
	for(;num!=0;num--)
	{
		HT1621_SET_WR(0);
		byte = ((dat&0x80)>>7);
//        GPIO_WriteBit(GPIOA, GPIO_Pin_12, byte);
        HT1621_SET_DAT(byte);
		HT1621_SET_WR(1);
		dat<<=1;
	}
}

uint8_t Read_TIMING(void)
{
    static uint8_t byte_data = 0;
    uint8_t num = 4;
    
	for(;num!=0;num--)
	{
		HT1621_SET_WR(0);
        byte_data += HT1621_READ_DAT;
		HT1621_SET_WR(1);   
	}
    
    return byte_data;
}

void Write_Cmd(uint8_t cmd)
{
	HT1621_SET_CS(0);
	Write_TIMING(0x80,4);
	Write_TIMING(cmd,8);
	HT1621_SET_CS(1);
}

void Write_Dat(uint8_t addr,uint8_t dat)
{
	HT1621_SET_CS(0);
	Write_TIMING(0xA0,3);		/* 101 */
	Write_TIMING(addr<<2,6);
	Write_TIMING(dat<<4,4);
	HT1621_SET_CS(1);
}

uint8_t Read_Dat(uint8_t r_addr)
{
    static uint8_t r_data;
    
	HT1621_SET_CS(0);
	Write_TIMING(0xC0,3);		/* 110 */
	Write_TIMING(r_addr<<2,6);
	r_data = Read_TIMING();
	HT1621_SET_CS(1);
    
    return r_data;
}

void Writer_Watt(uint16_t num)
{
    static char bai, shi, ge;
    
    bai = num / 100;
    shi = (num/10) % 10;
    ge = num % 10;
    
    if(num >= 100)
    {
        Write_Dat(0x02, (numble[bai]&0xF0)>>4);
        Write_Dat(0x03, (numble[bai]&0x0F));
        Write_Dat(0x04, (numble[shi]&0xF0)>>4);
        Write_Dat(0x05, (numble[shi]&0x0F));
        Write_Dat(0x06, (numble[ge]&0xF0)>>4);
        Write_Dat(0x07, (numble[ge]&0x0F));
    }
    else if(num >= 10)
    {
        Write_Dat(0x02, 0x00);
        Write_Dat(0x03, 0x00);
        Write_Dat(0x04, (numble[shi]&0xF0)>>4);
        Write_Dat(0x05, (numble[shi]&0x0F));
        Write_Dat(0x06, (numble[ge]&0xF0)>>4);
        Write_Dat(0x07, (numble[ge]&0x0F));
    }
    else
    {
        Write_Dat(0x02, 0x00);
        Write_Dat(0x03, 0x00);
        Write_Dat(0x04, 0x00);
        Write_Dat(0x05, 0x00);
        Write_Dat(0x06, (numble[ge]&0xF0)>>4);
        Write_Dat(0x07, (numble[ge]&0x0F));
    }
    
}

void Writer_Voltage(float v_num)
{
    static char v_bai, v_shi, v_ge, peanut;
    static uint16_t v_number;
    
    v_number = (uint16_t)(v_num * 10.0);
    v_bai = v_number / 1000;
    v_shi = (v_number/100) % 10;
    v_ge = (v_number/10) % 10;
    peanut = v_number % 10;
    
    if(v_number >= 1000)
    {
        Write_Dat(0x08, (numble[v_bai]&0xF0 | 0x80)>>4);
        Write_Dat(0x09, (numble[v_bai]&0x0F));
        Write_Dat(0x0A, (numble[v_shi]&0xF0)>>4);
        Write_Dat(0x0B, (numble[v_shi]&0x0F));
        Write_Dat(0x0C, (numble[v_ge]&0xF0)>>4);
        Write_Dat(0x0D, (numble[v_ge]&0x0F));
    }
    else if(v_number >= 100)
    {
        Write_Dat(0x08, (numble[v_shi]&0xF0 | 0x80)>>4);
        Write_Dat(0x09, (numble[v_shi]&0x0F));
        Write_Dat(0x0A, (numble[v_ge]&0xF0)>>4);
        Write_Dat(0x0B, (numble[v_ge]&0x0F));
        Write_Dat(0x0C, (numble[peanut]&0xF0|0x80)>>4);
        Write_Dat(0x0D, (numble[peanut]&0x0F));
    }
    else
    {
        Write_Dat(0x08, 0x08);
        Write_Dat(0x09, 0x00);
        Write_Dat(0x0A, (numble[v_ge]&0xF0)>>4);
        Write_Dat(0x0B, (numble[v_ge]&0x0F));
        Write_Dat(0x0C, (numble[peanut]&0xF0|0x80)>>4);
        Write_Dat(0x0D, (numble[peanut]&0x0F));
    }
  
}

void Writer_Msg(char v_type)
{
	  
    if(v_type == 1)
        Write_Dat(0x00, 0x02);
    else
        Write_Dat(0x01, 0x02);
}

void Writer_LCD(uint8_t COM1,uint8_t COM2,uint8_t COM3,uint8_t COM4)
{
	  
    Write_Dat(0x00, COM1);
		Write_Dat(0x01, COM2);
		Write_Dat(0x02, COM3);
		Write_Dat(0x03, COM4);
        
}

  
  
/******************* (C) COPYRIGHT 2018 TenPao Ltd. *****END OF FILE****/

