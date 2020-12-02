/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  LVD���򣺲��뿪����5V�л���3.3Vʱ��LVD������3.9V��ѹ�����л���5V�������LED1-LED4
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();                      //ϵͳ�δ��ʼ��
    LightInit();

    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4

    SCU_RegUnLock();
    SCU_LVDVS_3V9();
    SCU_LVDIFS_Fall();
    SCU_LVDFLT_Enable();
    NVIC_Init(NVIC_LVD_IRQn,NVIC_Priority_0,ENABLE);  //�ж�����
    SCU_LVD_Enable();
    SCU_LVDIT_Enable();
    SCU_RegLock();

    while(1);
}
