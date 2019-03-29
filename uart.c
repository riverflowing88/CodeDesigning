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
#include "main.h"

uint16_t recvCrc;
uint16_t  calcrc = 0;
uint16_t  StartCheckSum = 0;
uint16_t  MsgCheckSum = 0;


/*********************************************************
函数名: void UARTInit(void)
描  述: UART初始化子程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void UART0Init(void)
{
    GPIO_InitSettingType x;
    UART_InitStruType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A23, &x);        //TXD - PA23

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func1;
    x.Dir = GPIO_Direction_Input;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &x);        //RXD - PA22

    y.UART_StopBits = UART_StopBits_1;  //停止位：1
    y.UART_TxMode = UART_DataMode_8;    //发送数据格式：8位数据
    y.UART_TxPolar = UART_Polar_Normal; //发送端口极性：正常
    y.UART_RxMode = UART_DataMode_8;    //接收数据格式：8位数据
    y.UART_RxPolar = UART_Polar_Normal; //接收端口极性：正常
    y.UART_BaudRate = 1200;             //波特率
    y.UART_ClockSet = UART_Clock_1;     //时钟选择：Pclk
    UART_Init(UART0, &y);

    UART_BaudFreeConfig(UART0, UART_AUTO_BAUD_FREE_MODE1);//使能空闲检测,检测连续10个比特位空闲

    UART_TBIMConfig(UART0, UART_TBIM_Byte);
    UART_RBIMConfig(UART0, UART_TBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, Enable);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, Enable);

    UART0_TxEnable();
    UART0_RxEnable();
}

/*********************************************************
函数名: void UARTInit(void)
描  述: UART初始化子程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void UART1Init(void)
{
    GPIO_InitSettingType x;
    UART_InitStruType y;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func2;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B1, &x);        //TXD - PB1

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Func = GPIO_Reuse_Func2;
    x.Dir = GPIO_Direction_Input;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B0, &x);        //RXD - PB0

    y.UART_StopBits = UART_StopBits_1;  //停止位：1
    y.UART_TxMode = UART_DataMode_8;    //发送数据格式：8位数据
    y.UART_TxPolar = UART_Polar_Normal; //发送端口极性：正常
    y.UART_RxMode = UART_DataMode_8;    //接收数据格式：8位数据
    y.UART_RxPolar = UART_Polar_Normal; //接收端口极性：正常
    y.UART_BaudRate = 9600;             //波特率
    y.UART_ClockSet = UART_Clock_1;     //时钟选择：Pclk
    UART_Init(UART1, &y);

    UART_BaudFreeConfig(UART1, UART_AUTO_BAUD_FREE_MODE1);//使能空闲检测,检测连续10个比特位空闲

    UART_TBIMConfig(UART1, UART_TBIM_Byte);
    UART_RBIMConfig(UART1, UART_TBIM_Byte);
    UART_ITConfig(UART1, UART_IT_RB, Enable);
    NVIC_Init(NVIC_UART1_IRQn, NVIC_Priority_1, Enable);

    UART1_TxEnable();
    UART1_RxEnable();
}

uint8_t strAssign(StringType *String,uint8_t *chars)
{
  uint8_t i;
//  if(strlen(chars)>MAXSIZE+1){
//    return 0;
//  }
	String->len = sizeof(chars) / sizeof(uint8_t); 
  for(i = 0;i<String->len;i++){
    String->ch[i] = *(chars+i);
		String->chsum += *(chars+i);
  }
  String->ch[i] = (String->chsum>>8)&0xff;//??
  String->ch[i+1] = String->chsum&0xff;//??
	String->chsum = 0x00;
  String->len = String->len+2;  
  return 1;
}

//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void UART_Send_Data(UART_TypeDef *UARTx,uint8_t *buf,uint8_t len)
{
	uint8_t t=0;
	uint32_t getFlagStaCnt = 0;
	//RS485_TX_EN=1;			//设置为发送模式
  while(t < len)
  {     
		UART_SendByte(UARTx,buf[t++]);
		getFlagStaCnt = 0;
		while(UART_GetFlagStatus(UARTx, UART_FLAG_TB) == RESET)
		{
				getFlagStaCnt++;
				if (getFlagStaCnt > USART_GETFLAGSTATUSTOTAL)
				{
						break;
				}
		}
		UART_ClearITPendingBit(UARTx,UART_CLR_TC);
	}	 
	getFlagStaCnt = 0;
	while(UART_GetFlagStatus(UARTx, UART_FLAG_TC) == RESET)
	{
			getFlagStaCnt++;
			if(getFlagStaCnt > USART_GETFLAGSTATUSTOTAL)
			{
					break;
			}
	}
	UART_ClearITPendingBit(UARTx,UART_CLR_TC);	

}

void Uart_MSG_Deal(void)
{
	uint8_t i = 0,j=0;
	if(Rxd0Cnt >= 30){
			for(i=0;i<30;i++){
					if((Rx0Buff[i] == 0x55)&&(Rx0Buff[i+1] == 0x03)&&(Rx0Buff[i+2] == 0x01)){
							for(j=i;j<i+4;j++){
								StartCheckSum += Rx0Buff[j];
								Rxd0Cnt = 0;
							}
							
							if(StartCheckSum == ((Rx0Buff[i+4]<<8)+Rx0Buff[i+5])){
								AfterStage.Flag.RecStart = 1;
							}
							StartCheckSum = 0;
					}
				
					if((Rx0Buff[i] == 0x55)&&(Rx0Buff[i+1] == 0x05)){//0x55 05 00 00 00 00 00 crc
						for(j=i;j<i+7;j++){
								MsgCheckSum += Rx0Buff[j];
							  if(j==i+6){
							    AfterStage.Flag.Err = Rx0Buff[j];
								}
								//Rxd0Cnt = 0;
						}
						if(MsgCheckSum == ((Rx0Buff[i+7]<<8)+Rx0Buff[i+8])){
								AfterStage.Flag.RecMsg = 1;
						}
						MsgCheckSum =0;
						//recCheckSum = 0;
					}
				}
				Rxd0Cnt = 0;
				memset(Rx0Buff,0,RX0BUFSIZE);
				memset(rxFrame.RecBuff,0,RX0BUFSIZE);
			
	}
}


