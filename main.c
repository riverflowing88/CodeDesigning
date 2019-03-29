/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������ 
            �Զ��������жϣ�����⵽����֡�󣬴����жϣ�����Byte��������ͬByte
*��  ע:  ������HR8P506оƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t recv0_finish = 0;
uint8_t recv1_finish = 0;
uint8_t Rx1Buff[RX1BUFSIZE]={0};   //????????
uint8_t Rx0Buff[RX0BUFSIZE]={0};   //????????
uint8_t Rx1BuffLen;
uint8_t Rxd1Cnt=0;
uint8_t Rxd0Cnt=0;
uint16_t adc_value;
uint8_t key1_hold_time;
volatile uint32_t system1msTicker; 
volatile uint16_t systemSecTicker; 
volatile uint16_t system1secTicker;
AdcStructType Adc;
//uint8_t buf[] = {1,2,3,4,5,6,7,8};
uint8_t I2C_WriteFlag = 0;
uint8_t g_key_cmd;
RxFrameDef rxFrame;
TxFrameDef txFrame;
TimerType Timer;
IOOutBlinkTypeDef BuzzerSingValue;
WarnFlagType warningFlag;
__IO uint16_t SysErr = ERR_NONE;
StringType String;
//MainSwType MainSw;

void delay(void)
{
	int i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{;}
	}
}

uint8_t rbuf[4];
uint8_t wbuf[4];
uint8_t addr;         //Ƭ�ڵ�ַ
uint8_t addr_h;       //Ƭ�ڵ�ַ�߰��ֽڣ���ʾλ��led_buf[0]��
uint8_t addr_l;       //Ƭ�ڵ�ַ�Ͱ��ֽڣ���ʾλ��led_buf[1]��
uint8_t g_10ms_flag;
uint8_t StartStr1[4] ={0x55,0x03,0x01,0x00};
uint8_t StopStr1[4] ={0x55,0x03,0x00,0x00};
AfterStageType AfterStage;


int main(void)
{
	  //char i =0;
    SystemInit();
    DeviceClockAllEnable();
    User_SysTickInit();
	  CLK_Init();
	
    UART0Init();                         //UART��ʼ��(2400,8,NO,1)������ͨ��
	  UART1Init();                         //UART��ʼ��(9600,8,NO,1)��BMSͨ��
	  ScreenInit();
    SwitchInit();
    AdcInit();
	  //ADCACPConfig();
    //ADC_Start();
	
	  T16NxInit();
	  IICMasterInit();
	  TM1621Init();
	  //I2C_Init();
	  addr_h = 0x00;                                                  //��ʼ����ַ
    addr_l = 0x00;
    addr = (addr_h << 4) + addr_l;  
    g_10ms_flag = 1;  
	  Freq = Hz_50;
	  SHUT_DOWN_ON;
		Timer.Flag.Stop = 1;
		Timer.Flag.StopFinish = 1;
	  warningFlag.bit.alarm = 0;
		HT1621_SET_BACK(0);
		FAN_ON;
    //SMBUS_WriteByte(SLAVE_ADDR, addr,1, wbuf);
		//IIC0_MasterReadData(SLAVE_ADDR, addr, rbuf, 1);    //д��1���ֽ�EEPROM����
		//I2C_Puts(0xA0,0x00,4,wbuf);
    while(1)
    {   
	    static uint16_t ticker1Ms = 0;
        static uint16_t ticker10Ms = 0;
        static uint16_t ticker200Ms = 0;
        static uint16_t ticker1s = 0;
        static uint16_t ticker5s = 0;
        //static uint16_t ticker10s = 0;
        //static uint8_t acInCnt = 0;
        //????????   
        if(getAbsTickMs(ticker5s) >= 5000){
            ticker5s = system1msTicker;
						//Writer_Watt(400);
						//Writer_Voltage(89.5);
						Writer_LCD(DC_B|USB|S5,Charge|Light|AC_B, Freq_50|Freq_Hz,S1|S2);
        ////////////////////////////////???1s???????///////////////////////////////////////////////         
        }else if(getAbsTickMs(ticker1s) >= 1000){
            ticker1s = system1msTicker;
            system1secTicker++;
            systemSecTicker++;
						
					  
					  
					  //I2C_Gets(0xA0,0x00,4,rbuf);
//			      if(g_10ms_flag == 1){
//								//g_10ms_flag = 0;
//								//g_key_cmd = KeyGetValue();
//								g_key_cmd = 1;

//								switch(g_key_cmd)
//								{
//									case 1:                                                 // write 0x00
//											wbuf[0] = 0x01;    
//											IIC0_MasterWriteData(SLAVE_ADDR, addr, wbuf, 1);    //д��1���ֽ�EEPROM����
////									    SMBUS_WriteByte(SLAVE_ADDR, addr,1, wbuf);
////											Delay_100us(100);
////											SMBUS_WriteByte(SLAVE_ADDR, addr,1, rbuf);
//											break;
//									case 2:                                                 // write current addr
//											wbuf[0] = addr;    
//											SMBUS_WriteByte(SLAVE_ADDR, addr,1, wbuf);
//											Delay_100us(100);
//											SMBUS_WriteByte(SLAVE_ADDR, addr,1, rbuf);
//											break;
//									default:
//											g_key_cmd = 0;
//											break;
//								}
//						}
        ////////////////////////////////???1s???????///////////////////////////////////////////////         
        }else if(getAbsTickMs(ticker200Ms) >= 200){
            ticker200Ms = system1msTicker;
					  
						//BatHighLowVoltProtect();//LowVolt:11V,HighVolt:18V
        ////////////////////////////////???100ms???????///////////////////////////////////////////// 
        }else if(getAbsTickMs(ticker10Ms) >= 10){
            ticker10Ms = system1msTicker; 
			BuzzerSing();
            excuteAlarmCmd();
		    GetAdcResult();
			StartCtrl();
			ChgFreqCtrl();

        ////////////////////////////////???10ms???????//////////////////////////////////////////////     
        }else if(ticker1Ms != system1msTicker){
            ticker1Ms = system1msTicker; 
					  
		    Uart_MSG_Deal();
					if(Timer.Flag.dotClick == 1){
						Timer.mSec++;
						if(Timer.mSec > 1000){
							Timer.Sec++;
							Timer.mSec = 0;
							if(Timer.Sec >30){
								Timer.Sec = 0;
								HT1621_SET_BACK(0);
								Timer.Flag.dotClick = 0;
								if(Timer.Flag.Stop == 1){
									MAIN_SW_OFF;
								}
							}
						}
					}
					  //PIN19_H;
					  //PIN18_H;
					  //PIN17_H;
					  //PIN16_H;  
        }

	}
//		//if ((GPIO_ReadBit(GPIO_Pin_B1)) == 0)
//		GetAdcResult();
//		//Adc.Vin = ADCRead();
//		if((GPIO_ReadBit(GPIO_Pin_B9)==0)&&(GPIO_ReadBit(GPIO_Pin_A23)==0)) //����˯��ģʽ
//		{
//			sleep(); //�������ߺ���
//			__enable_irq();    //ʹ��ȫ���ж�
//		}
//		/*if((GPIO_ReadBit(GPIO_Pin_A7)) == 1)
//		{
//			key1_hold_time++;
//			if(key1_hold_time >= 10)
//			{
//				adc_value = 0;
//				sleep();
//				__enable_irq(); //�ر�IRQ���ж�
//				key1_hold_time = 0;
//			}
//		}*/
//        if(1 == recv0_finish)
//        {
//            //recv_finish = 0;
//            UART_SendByte(UART0, Rx0Buff[Rxd0Cnt++]);
//        }
//		    if(1 == recv1_finish)
//        {
//            //recv_finish = 0;
//            UART_SendByte(UART1, Rx1Buff[Rxd1Cnt++]);
//        }
//				//WDT_Clear();  //�幷
//    }
}



