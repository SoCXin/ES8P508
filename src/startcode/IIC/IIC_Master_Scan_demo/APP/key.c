/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  key.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  KEY模块程序
          R1~R2行输出，L1~L2列输入
                  |    L1    L2
                --|--------
                R1|    K2    K1 
                R2|    K4    K3
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "key.h"

uint8_t key1_press_flag;     //按键按下标志
uint8_t key2_press_flag;
uint8_t key3_press_flag;
uint8_t key4_press_flag;
uint8_t key5_press_flag;

uint8_t key1_hold_time;      //按键消抖时间    
uint8_t key2_hold_time;
uint8_t key3_hold_time;
uint8_t key4_hold_time;
uint8_t key5_hold_time;

/*********************************************************
函数名: void KeyInit(void)
描  述: 按键初始化子程序
输入值: 无
输出值: 无
返回值: 无 
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
函数名: void WakeupInit(void)
描  述: 按键中断唤醒初始化子程序
输入值: 无
输出值: 无
返回值: 无 
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
    GPIO_Init(GPIOA,GPIO_Pin_20,&x);    //初始化KINT按键

    PINT_Config(PINT4, PINT_SEL2, PINT_Trig_Rise);          //选择SEL2中断源，上升沿触发中断
    NVIC_Init(NVIC_PINT4_IRQn,NVIC_Priority_2,ENABLE);
    PINT4_MaskDisable();
    PINT4_Enable();                       //开启KINT中断
}
/*********************************************************
函数名: uchar KeyGetValue(void)
描  述: 按键驱动子程序，判断按键状态，读取键值
输入值: 无
输出值: 无
返回值: 1 - K1
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
    GPIO_Init(GPIOB,GPIO_Pin_8,&x);   //设置KR1为输出

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

    GPIOB_SetBit(GPIO_Pin_8);   //KR1输出高电平

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_8,&x);                //设置KR1为输入

/*-------------------------------------------------------*/
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
		x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_3,&x);                    //设置KR2为输出

    GPIOB_ResetBit(GPIO_Pin_3);                        //KR2输出低电平

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

    GPIOB_SetBit(GPIO_Pin_3);                        //KR2输出高电平

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_3,&x);                    //设置KR2为输入

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


