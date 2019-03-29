/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  sleep.c
*��  ��:  
*��  ��:  V1.01
*��  ��:  2018/03/26
*��  ��:  ���ߺ���
*��  ע:  ������HRSDK-GDB-8P506
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "sleep.h"

/***************************************************************
 ��������void sleep(void)
 ��  �������ߺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void sleep(void)
{
    GPIO_InitSettingType y; 
    KINT_InitSettingType z; 
	PINT_InitSettingType x; 
    __disable_irq(); //�ر�IRQ���ж�
    WDT_Clear();  //�幷
    DeviceClockAllEnable();

    GPIO->PAINEB.Word = 0XFFFFFFFF; //����ر�
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //�����
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00000000;  //PA6����߹ر�LED1
    GPIO->PBDATA.Word = 0X00000000;  //PB7����������

    y.Signal = GPIO_Pin_Signal_Digital;
    y.Func = GPIO_Reuse_Func0;
    y.Dir = GPIO_Direction_Input;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE= GPIO_PUE_Input_Disable;
    y.PDE= GPIO_PDE_Input_Enable;
    GPIO_Init(GPIO_Pin_B9, &y);
	  GPIO_Init(GPIO_Pin_A23, &y);


    z.IE_Set = KINT_IE_Set_Enable;
    z.Trigger_Style = KINT_Trigger_Rising_Edge;
    KINT_Init(GPIO_Pin_B9, &z);                     //��ʼ�������ж�

	  x.IE_Set = PINT_IE_Set_Enable;
    x.Trigger_Style = PINT_Trigger_Rising_Edge;
    PINT_Init(GPIO_Pin_A23, &x);                     //��ʼ�������ж�

	  KINT_ClearITFlag(GPIO_Pin_B9);      //�����־λ
	  PINT_ClearITFlag(GPIO_Pin_A23);      //�����־λ	    SCU_RegUnLock();
    SCU_LVDVS_4V();    //LVD���ѵ�ѹ4V
    SCU_LVDIFS_Fall(); //LVD��ѹ���߼��
    SCU_LVDFLT_Enable(); //LVD�˲�ʹ��
    SCU_LVD_Enable(); //LVD�ж�ʹ��
    SCU->WAKEUPTIME.MOSC_EN = 0; //��˯����ʱ���Զ��ر�
    SCU->WAKEUPTIME.WAKEUPTIME = 20; //����ʱ�䲻��С��40us
    SCB_SystemLPConfig(SCB_LP_SleepDeep, Enable);  //���˯��ģʽ 
    SCU_RegLock();


//    WDT_RegUnLock();//WDT�ر�д����
//    WDT_ITEnable(); //IEʹ��

//    NVIC_EnableIRQ(LVD_IRQn);  //ʹ��LVD����Դ
//    NVIC_EnableIRQ(WDT_IRQn);  //ʹ��WDT����Դ
    NVIC_EnableIRQ(KINT_IRQn); //ʹ�ܰ�������
	  NVIC_EnableIRQ(PINT7_IRQn); //ʹ�ܰ�������


//    while (1) //������ѭ��
//    {
//      SCU_RegUnLock();
//      SCU->SCLKEN0.SYSCLK_DIV = 5;// ϵͳʱ�Ӻ��Ƶ1:32 //ϵͳʱ�����ڲ���С��2us
//      __WFI(); //����
//      SCU->SCLKEN0.SYSCLK_DIV = 0;// �ָ�ϵͳʱ�Ӻ��Ƶ��
//      SCU_RegLock();

//      NVIC->ICPR[0] = 0XFFFFFFFF; //��NVIC�����ʶ
////      if(WDT_GetFlagStatus() != RESET)
////      {
////        WDT_Clear();  //�幷
//////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////      }
////      if(SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)  //LVD����
////      {
////        SCU_RegUnLock();
////        SCU_LVDClearIFBit();
////        SCU_RegLock();
////        NVIC_SystemReset();   //��λ����
////      }
//      if(KINT_GetITFlag(GPIO_Pin_B9) != RESET)   //KINT����
//      {
//        KINT_ClearITFlag(GPIO_Pin_B9);      // ��������жϱ�־λ
//        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
////        GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
//      }
//    }
    __asm("WFI");
    __asm("NOP");												//�����ڴ˴�	
}
