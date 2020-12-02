/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  adc.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  ADCģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "adc.h"
#include "ES8P508x.h"

/*********************************************************
������: void ADC0_UserInit(void)
��  ��: ADC��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
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

    y.ADC_ClkS = ADC_ClkS_PCLK;          //ʱ�ӣ�PCLK
    y.ADC_ClkDiv = ADC_ClkDiv_32;        //Ԥ��Ƶ��1:32  ADCת��ʱ��Դһ��Ҫ���������ֲ���ADCת��ʱ��Դѡ���
    y.ADC_VrefP = ADC_VrefP_Vcc;         //����ο���ѹ��VDD
    y.ADC_SampS = ADC_SMPS_HARD;         //AD����ģʽѡ��Ӳ��
    y.ST = 7;
    y.ADC_VREFN = DISABLE;
    y.ADC_VRBUF_EN = ENABLE;
    ADC_Init(&y);                        //���սṹ��Ĳ�������ADC

    ADC_IE_Disable();                    //��ʹ���ж�
    ADC_Enable();                        //ʹ��ADC
}

/*********************************************************
������: uint16_t ADCRead(void)
��  ��: ��ȡADC����ֵ�����˲�
����ֵ: ��
���ֵ: ��
����ֵ: ����ֵ
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
