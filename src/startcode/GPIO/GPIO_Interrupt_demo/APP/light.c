/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  light.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  LIGHTָʾ��ģ�麯��
*��  ע:  ������HRSDK-GDB-ES8P508 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "light.h"

/***************************************************************
 ��  ����LIGHTָʾ�Ƴ�ʼ��
 ����ֵ����
 ����ֵ����
***************************************************************/
void LightInit(void)
{
    GPIO_InitStruType x;

    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = DISABLE;
    x.GPIO_PDEN = ENABLE;
    x.GPIO_OD = DISABLE;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    x.GPIO_INEB = GPIO_INEB_DISABLE;

    GPIO_Init(GPIOA,GPIO_Pin_31,&x);    //LD1
    GPIO_Init(GPIOA,GPIO_Pin_2,&x);     //LD2
    GPIO_Init(GPIOA,GPIO_Pin_3,&x);     //LD3
    GPIO_Init(GPIOA,GPIO_Pin_4,&x);     //LD4
}

