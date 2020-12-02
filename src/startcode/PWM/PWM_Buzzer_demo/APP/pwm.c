/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  pwm.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  PWM模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "pwm.h"

/*********************************************************
函数名: void User_T16N2_PWMInit(void)
描  述: T16N2定时器初始化：PWM输出
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void User_T16N2_PWMInit(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;                 //选择时钟：Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                 //设为PWM模式
    T16Nx_BaseInit(T16N2,&x);

    T16N2_PwmOut1_Enable();                     //使能端口输出1
    T16Nx_MAT2Out1Config(T16N2,TIM_Out_High);   //匹配2：输出高
    T16Nx_MAT3Out1Config(T16N2,TIM_Out_Low);    //匹配3：输出低

    T16Nx_SetPREMAT(T16N2,5);                   //预分频
    T16Nx_SetMAT2(T16N2,3000);                  //控制占空比
    T16Nx_SetMAT3(T16N2,6000);                  //控制频率

    T16Nx_MAT2ITConfig(T16N2,TIM_Go_Int);       //匹配2：继续计数
    T16Nx_MAT3ITConfig(T16N2,TIM_Clr_Int);      //匹配3：清0

    T16Nx_ITConfig(T16N2,TIM_IT_MAT2,DISABLE);    //可选择是否使能中断
    T16Nx_ITConfig(T16N2,TIM_IT_MAT3,DISABLE);
    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,DISABLE);       //打开或关闭总中断
    T16N2_Enable();                             //使能定时器 
}    

/*********************************************************
函数名: void PWMOutput(uint32_t temp)
描  述: T16N2 PWM输出设置频率，占空比固定为50%，供播放音乐使用
输入值: 控制频率数值
输出值: 无
返回值: 无 
**********************************************************/
void PWMOutput(uint16_t temp)
{
    T16Nx_SetMAT2(T16N2,temp/2);    //低电平时间
    T16Nx_SetMAT3(T16N2,temp);      //总时间
    T16Nx_SetCNT(T16N2,0);          //设置后一定要清除CNT计数器重新计数！！！
}
