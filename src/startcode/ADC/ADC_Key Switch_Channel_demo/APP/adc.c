/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  adc.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述:  ADC模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "adc.h"
#include "ES8P508x.h"

/*********************************************************
函数名: void ADC0_UserInit(void)
描  述: ADC初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void ADC0_UserInit(void)
{
    GPIO_InitStruType x;
    ADC_InitStruType y;

    x.GPIO_Signal = GPIO_Pin_Signal_Analog;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB, GPIO_Pin_6, &x);    //PB6
    GPIO_Init(GPIOB, GPIO_Pin_5, &x);    //PB5

    y.ADC_ClkS = ADC_ClkS_PCLK;          //时钟：PCLK
    y.ADC_ClkDiv = ADC_ClkDiv_32;        //预分频：1:32  ADC转换时钟源一定要符合数据手册中ADC转化时钟源选择表
    y.ADC_VrefP = ADC_VrefP_Vcc;         //正向参考电压：VDD
    y.ADC_SampS = ADC_SMPS_HARD;         //AD采样模式选择：硬件
    y.ST = 7;
    y.ADC_VREFN = DISABLE;
    y.ADC_VRBUF_EN = ENABLE;
    ADC_Init(&y);                        //按照结构体的参数配置ADC

    ADC_IE_Disable();                    //不使能中断
    ADC_Enable();                        //使能ADC
}

/*********************************************************
函数名: uint16_t ADCRead(void)
描  述: 读取ADC采样值，带滤波
输入值: 无
输出值: 无
返回值: 采样值
**********************************************************/
uint16_t ADCRead(void)
{
    uint8_t i;
    uint16_t max, min, sum, ad_temp;

    max = 0x00;
    min = 0x0fff;
    sum = 0x00;

    for (i = 0; i < 18; i++)
    {
        ADC_Start();

        while (ADC_GetFlagStatus(ADC_IF) == RESET);

        ad_temp = ADC_GetConvValue();
        ADC_ClearIFStatus(ADC_IF);

        if (ad_temp > max)
        {
            max = ad_temp;
        }

        if (ad_temp < min)
        {
            min = ad_temp;
        }

        sum += ad_temp;
    }

    sum -= min;
    sum -= max;
    return (sum >> 4);
}
