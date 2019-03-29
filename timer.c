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
#include "timer.h"

/*********************************************************
������: void T16N3Init(void)
��  ��: T16N3��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16NxInit(void)
{
    T16Nx_BaseInitStruType x;

    /* ��ʼ��T16Nx��ʱ��*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;                     //�ڲ�ʱ��PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //��ʱ��������ģʽ
    x.T16Nx_PREMAT = 1;
    T16Nx_BaseInit(T16N0,&x);                           //��ʼ����ʱ��T16N0
    T16Nx_BaseInit(T16N1,&x);                           //��ʼ����ʱ��T16N1
    T16Nx_BaseInit(T16N2,&x);                           //��ʼ����ʱ��T16N2
    T16Nx_BaseInit(T16N3,&x);                           //��ʼ����ʱ��T16N3

    /* ���ö�ʱ����ÿ��40000��ϵͳʱ�Ӳ���һ���ж� */
    T16Nx_MAT0ITConfig(T16N0,T16Nx_Clr_Int);            //MAT0ƥ������
    T16Nx_MAT0ITConfig(T16N1,T16Nx_Clr_Int);            //MAT0ƥ������
    T16Nx_MAT0ITConfig(T16N2,T16Nx_Clr_Int);            //MAT0ƥ������
    T16Nx_MAT0ITConfig(T16N3,T16Nx_Clr_Int);            //MAT0ƥ������
    T16Nx_SetCNT0(T16N0,0);                             //����T16N0��ʼֵΪ0
    T16Nx_SetCNT0(T16N1,0);                             //����T16N1��ʼֵΪ0
    T16Nx_SetCNT0(T16N2,0);                             //����T16N2��ʼֵΪ0
    T16Nx_SetCNT0(T16N3,0);                             //����T16N3��ʼֵΪ0

    T16Nx_SetMAT0(T16N0,16000);                         //����T16N0MAT0ֵΪ40000
    T16Nx_SetMAT0(T16N1,16000);                         //����T16N1MAT0ֵΪ40000
    T16Nx_SetMAT0(T16N2,16000);                         //����T16N2MAT0ֵΪ40000
    T16Nx_SetMAT0(T16N3,40000);                         //����T16N3MAT0ֵΪ40000

    T16Nx_ITConfig(T16N0,T16Nx_IT_MAT0,Enable);         //ʹ��T16N0ƥ��0�ж�
    T16Nx_ITConfig(T16N1,T16Nx_IT_MAT0,Enable);         //ʹ��T16N1ƥ��0�ж�
    T16Nx_ITConfig(T16N2,T16Nx_IT_MAT0,Enable);         //ʹ��T16N2ƥ��0�ж�
    T16Nx_ITConfig(T16N3,T16Nx_IT_MAT0,Enable);         //ʹ��T16N3ƥ��0�ж�

    NVIC_Init(NVIC_T16N0_IRQn,NVIC_Priority_1,Enable);  //�ж�����
    NVIC_Init(NVIC_T16N1_IRQn,NVIC_Priority_1,Enable);  //�ж�����
    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,Enable);  //�ж�����
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,Enable);  //�ж�����

    T16Nx_Enable(T16N0);
    T16Nx_Enable(T16N1);
    T16Nx_Enable(T16N2);
    T16Nx_Enable(T16N3);

}



