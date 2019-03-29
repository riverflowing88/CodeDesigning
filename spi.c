/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  SPI����ģ�����
          ����EEPROM
*��  ע:  ������HRSDK-GDB-HR8P506
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

/*********************************************************
������: void SPIInit(void)
��  ��: SPI������ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void SPI1Init(void)
{
    GPIO_InitSettingType x;
    SPI_InitStruType y;

    /* PA 24 25 26 27 */
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A24, &x);                //DO  - PA24
    GPIO_Init(GPIO_Pin_A25, &x);                //DI  - PA25
    GPIO_Init(GPIO_Pin_A3, &x);                //CLK - PA26

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A27, &x);                //CS/NSS  - PA27

    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_FallSendRiseRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = Enable;                   //��ʱ������
    y.SPI_DelaySend = Disable;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(SPI1, &y);                         //���սṹ��Ĳ�������SPI

    SPI1_Enable();                              //ʹ��SPI
}

/*********************************************************
������: void SPI0_Ewen(void)
��  ��: EEPROMдʹ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void SPI1_Ewen(void)
{
    GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
    SPI_SendByte(SPI1, 0x02);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x60);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    GPIO_WriteBit(GPIO_Pin_A27, 0);
}

/*********************************************************
������: void SPI0_Ewen(void)
��  ��: EEPROMд��ֹ
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void SPI1_Ewds(void)
{
    GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
    SPI_SendByte(SPI1, 0x02);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x00);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    GPIO_WriteBit(GPIO_Pin_A27, 0);
}

/*********************************************************
������: void SPIReadData(uchar addr, uchar *buf, uchar n)
��  ��: SPI�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: addr����ַ
        n���������ݸ���
���ֵ: buf���������ݻ���
����ֵ: ��
**********************************************************/
void SPI1ReadData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;

    GPIO_WriteBit(GPIO_Pin_A27, 1);                     //CS
    SPI_SendByte(SPI1, 0x03);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, addr);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    SPI1_RecEnable();                                   //ʹ�ܽ���

    for (i = 0; i<n; i++)                               //����
    {
        while(SPI_GetFlagStatus(SPI1, SPI_Flag_RB));    //��������ʱ�Ž���
        SPI_SendByte(SPI1, 0);                          //���ͽ����õ�ʱ��
        while(SPI_GetFlagStatus(SPI1, SPI_Flag_RB) == RESET);
        buf[i] = SPI_RecByte(SPI1);
    }

    GPIO_WriteBit(GPIO_Pin_A27, 0);                     //cs

    SPI1_RecDisable();                                  //��ֹ����
}

/*********************************************************
������: uchar SPIWriteData(uchar memory_addr, uchar *buf, uchar n)
��  ��: SPIд���ݣ�����ֽڱ��
����ֵ: addr����ַ
        buf���������ݻ���
        n���������ݸ���
���ֵ: ��
����ֵ: ��
**********************************************************/
void SPI1WriteData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A25, &x);            //MISO��Ϊ���룬�����ж���Ӧ

    SPI1_Ewen();                            //disд����
    Delay_100us(1);

    for (i = 0; i < n; i++)
    {
        GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS
        SPI_SendByte(SPI1, 0x02);
        while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
        SPI_SendByte(SPI1, 0x80 | (addr + i));
        while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
        SPI_SendByte(SPI1, buf[i]);
        while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
        GPIO_WriteBit(GPIO_Pin_A27, 1);     //CS

        while((GPIO_ReadBit(GPIO_Pin_A25)) == 0);  //�ȵ�MISO������

        GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS
    }

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A25, &x);        //DI  - PA25

    Delay_100us(1);
    SPI1_Ewds();                            //д����
}

/*********************************************************
������: void SPI0EraseAll(void)
��  ��: SPI����ȫƬ�����0xFF��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void SPI1EraseAll(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir  = GPIO_Direction_Input;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE  = GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_A25, &x);            //MISO��Ϊ���룬�����ж���Ӧ

    SPI1_Ewen();                            //disд����
    Delay_100us(1);

    GPIO_WriteBit(GPIO_Pin_A27, 1);         //CS
    SPI_SendByte(SPI1, 0x02);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);
    SPI_SendByte(SPI1, 0x40);
    while(SPI_GetStatus(SPI1, SPI_STA_IDLE) == RESET);

    GPIO_WriteBit(GPIO_Pin_A27, 0);         //CS
    GPIO_WriteBit(GPIO_Pin_A27, 0);         //CS
    GPIO_WriteBit(GPIO_Pin_A27, 1);         //CS

    while((GPIO_ReadBit(GPIO_Pin_A25)) == 0);  //�ȵ�MISO������ 

    GPIO_WriteBit(GPIO_Pin_A27, 0);     //CS    

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func1;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A25, &x);        //DI  - PA25

    Delay_100us(1);
    SPI1_Ewds();                            //д����
}  
