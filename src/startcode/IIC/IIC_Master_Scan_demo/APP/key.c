/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  key.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  KEYģ�����
          R1~R2�������L1~L2������
                  |    L1    L2
                --|--------
                R1|    K2    K1 
                R2|    K4    K3
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "key.h"

uint8_t key1_press_flag;     //�������±�־
uint8_t key2_press_flag;
uint8_t key3_press_flag;
uint8_t key4_press_flag;
uint8_t key5_press_flag;

uint8_t key1_hold_time;      //��������ʱ��    
uint8_t key2_hold_time;
uint8_t key3_hold_time;
uint8_t key4_hold_time;
uint8_t key5_hold_time;

/*********************************************************
������: void KeyInit(void)
��  ��: ������ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void KeyInit(void)
{
    GPIO_InitStruType x;

	  x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_7,&x);         //KL1
    GPIO_Init(GPIOB,GPIO_Pin_2,&x);         //KL2
    GPIO_Init(GPIOB,GPIO_Pin_8,&x);         //KR1
    GPIO_Init(GPIOB,GPIO_Pin_3,&x);         //KR2
    GPIO_Init(GPIOA,GPIO_Pin_20,&x);         //K5

    key1_press_flag = 0;
    key2_press_flag = 0;
    key3_press_flag = 0;
    key4_press_flag = 0;
    key5_press_flag = 0;

    key1_hold_time = 0;
    key2_hold_time = 0;
    key3_hold_time = 0;
    key4_hold_time = 0;
    key5_hold_time = 0;
}
/*********************************************************
������: void WakeupInit(void)
��  ��: �����жϻ��ѳ�ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void KINTInit(void)
{
    GPIO_InitStruType x;

	  x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_20,&x);    //��ʼ��KINT����

    PINT_Config(PINT4, PINT_SEL2, PINT_Trig_Rise);          //ѡ��SEL2�ж�Դ�������ش����ж�
    NVIC_Init(NVIC_PINT4_IRQn,NVIC_Priority_2,ENABLE);
    PINT4_MaskDisable();
    PINT4_Enable();                       //����KINT�ж�
}
/*********************************************************
������: uchar KeyGetValue(void)
��  ��: ���������ӳ����жϰ���״̬����ȡ��ֵ
����ֵ: ��
���ֵ: ��
����ֵ: 1 - K1
        2 - K2
        3 - K3
        4 - K4
        5 - K5
**********************************************************/
uint8_t KeyGetValue(void)
{
    uint8_t temp_key_value = 0;
    GPIO_InitStruType x;

	x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_8,&x);   //����KR1Ϊ���

    GPIOB_ResetBit(GPIO_Pin_8);

    if (GPIO_ReadBit(GPIOB,GPIO_Pin_2) == 0)    //KL2==0?
    {
        if (key1_press_flag == 0)
        {
            key1_hold_time++;
            if (key1_hold_time >= 2)
            {
                key1_hold_time = 0;
                key1_press_flag = 1;
            }
        }
    }
    else
    {
        if (key1_press_flag == 1)
        {
            key1_hold_time++;
            if (key1_hold_time >= 2)
            {
                key1_hold_time = 0;
                key1_press_flag = 0;
                temp_key_value = 1;
            }
        }
    }

    if (GPIO_ReadBit(GPIOB,GPIO_Pin_7) == 0)     //KL1==0?
    {
        if (key2_press_flag == 0)
        {
            key2_hold_time++;
            if (key2_hold_time >= 2)
            {
                key2_hold_time = 0;
                key2_press_flag = 1;
            }
        }
    }
    else
    {
        if (key2_press_flag == 1)
        {
            key2_hold_time++;
            if (key2_hold_time >= 2)
            {
                key2_hold_time = 0;
                key2_press_flag = 0;
                temp_key_value = 2;
            }
        }
    }

    GPIOB_SetBit(GPIO_Pin_8);   //KR1����ߵ�ƽ

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_8,&x);                //����KR1Ϊ����

/*-------------------------------------------------------*/
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
		x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_3,&x);                    //����KR2Ϊ���

    GPIOB_ResetBit(GPIO_Pin_3);                        //KR2����͵�ƽ

    if (GPIO_ReadBit(GPIOB,GPIO_Pin_2) == 0)    //KL2==0?
    {
        if (key3_press_flag == 0)
        {
            key3_hold_time++;
            if (key3_hold_time >= 2)
            {
                key3_hold_time = 0;
                key3_press_flag = 1;
            }
        }
    }
    else
    {
        if (key3_press_flag == 1)
        {
            key3_hold_time++;
            if (key3_hold_time >= 2)
            {
                key3_hold_time = 0;
                key3_press_flag = 0;
                temp_key_value = 3;
            }
        }
    }

    if (GPIO_ReadBit(GPIOB,GPIO_Pin_7) == 0)    //KL1==0?
    {
        if (key4_press_flag == 0)
        {
            key4_hold_time++;
            if (key4_hold_time >= 2)
            {
                key4_hold_time = 0;
                key4_press_flag = 1;
            }
        }
    }
    else
    {
        if (key4_press_flag == 1)
        {
            key4_hold_time++;
            if (key4_hold_time >= 2)
            {
                key4_hold_time = 0;
                key4_press_flag = 0;
                temp_key_value = 4;
            }
        }
    }

    GPIOB_SetBit(GPIO_Pin_3);                        //KR2����ߵ�ƽ

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_3,&x);                    //����KR2Ϊ����

    if (GPIO_ReadBit(GPIOA,GPIO_Pin_20) == 0) //KINT==0?
    {
        if (key5_press_flag == 0)
        {
            key5_hold_time++;
            if (key5_hold_time >= 2)
            {
                key5_hold_time = 0;
                key5_press_flag = 1;
            }
        }
    }
    else
    {
        if (key5_press_flag == 1)
        {
            key5_hold_time++;
            if (key5_hold_time >= 2)
            {
                key5_hold_time = 0;
                key5_press_flag = 0;
                temp_key_value = 5;
            }
        }
    }

    return temp_key_value;
}


