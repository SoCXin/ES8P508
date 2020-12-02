/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  
*��  ��:  V1.00
*��  ��:  2018/05/3
*��  ��:  sleepʾ�����򣬵���ʹ���Ӱ��������(��Ҫ�Ͽ��Ӱ��ϵ�Դָʾ�Ƶ���������)��
          �������ѹ����3.5V�������߳���
          �������ѹ����3.9V�˳����߳���PA23������ת
          ���߳�����Դ���£�
          1.�ṩWDT����
          2.��������(PA20��0)��PA23������ת7��
          3.LVD����ϵͳ��λ�˳����ߺ���
          4.RTC�뻽��PA23��תһ��
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t g_sleep_flag = 0;
int main(void)
{
    uint32_t i;
    GPIO_InitStruType x;
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��
    SysTickInit();                      //ϵͳ�δ��ʼ��

    //���¿�ʼ���LVD��ѹ�Ƿ��������͹���״̬
    SCU_RegUnLock(); //scuд��������
    SCU_LVDIFS_High(); //LVD�͵�ѹ���//�ߵ�ƽ���
    SCU_LVDVS_3V5();   //LVD���ߵ�ѹ3.5V
    SCU_LVDFLT_Enable(); //LVD�˲�ʹ��
    SCU_LVDIT_Enable(); //LVD�ж�ʹ��
    SCU_LVD_Enable();   //LVDʹ��
    SCU->PWRC.PORRSTF = 0;   //��Ҫ���SOFT_RSTF��ʶ���Ƚ�PORRSTF����//�ϵ縴λ��־
    SCU_RegLock();  //scuд��������

    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_Out) == SET)  //LVD��⵽��ѹ����4V
    {
   
     Sleep(1); //�������ߺ���
 
    }
 
 
    //���¿�ʼ������ѭ����ʼ��
    SCU_RegUnLock();
    SCU_LVDIFS_Rise(); //LVD��ѹ���ͼ��//�����ؼ��
    NVIC_Init(NVIC_LVD_IRQn,NVIC_Priority_0,ENABLE);  //LVD�ж�����//�ж����ȼ���Ϊ���
    SCU_OpenXTAL();  //ʹ���ⲿ����
    SCU_RegLock();
 
   
   
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;  
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS= GPIO_DS_Output_Normal;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    GPIO_Init(GPIOA,GPIO_Pin_23,&x); //PA23����Ϊ���
    GPIOA_SetBit(GPIO_Pin_6);
    GPIO_Init(GPIOA,GPIO_Pin_6,&x); //PA6����Ϊ���
    GPIOA_SetBit(GPIO_Pin_14);
    GPIO_Init(GPIOA,GPIO_Pin_14,&x);//PA14����Ϊ���

    if(SCU->PWRC.SOFT_RSTF == 0)  //����û�о�������λ
    {
      GPIOA_ToggleBit(GPIO_Pin_6);   //PA6��ת
      GPIOA_ResetBit(GPIO_Pin_14);   //PA14��ת������ѧϰ��ư���
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6��ת
      GPIOA_SetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6��ת
      GPIOA_ResetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6��ת
      GPIOA_SetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6��ת
      GPIOA_ResetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6��ת
      GPIOA_SetBit(GPIO_Pin_14);
    }

	while (1)
    {
                          
      GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
      IWDT_Clear();   //�幷
      if(g_sleep_flag == 1)   //LVD�жϼ�⵽VDD��ѹ����3.6V����λ�������ߺ���
      {
        NVIC_SystemReset();   
      }
    }
}
