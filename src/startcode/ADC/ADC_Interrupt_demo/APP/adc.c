/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  adc.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  ADCģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "adc.h"

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
    GPIO_Init(GPIOB,GPIO_Pin_6,&x);      //PB6

    y.ADC_ChS = ADC_CHS_AIN1;            //ͨ��:AIN1
    y.ADC_ClkS = ADC_ClkS_PCLK;          //ʱ�ӣ�PCLK
    y.ADC_ClkDiv = ADC_ClkDiv_32;        //Ԥ��Ƶ��1:32  ADCת��ʱ��Դһ��Ҫ���������ֲ���ADCת��ʱ��Դѡ���
    y.ADC_VrefP = ADC_VrefP_Vcc;         //����ο���ѹ���ڲ��ο���ѹVref 2.048V, AVREFP�˿ڸ���Ϊ��ͨIO��
    y.ADC_SampS = ADC_SMPS_HARD;         //AD����ģʽѡ��Ӳ��
    y.ST = 7;
	  y.ADC_VREFN = DISABLE;
    y.ADC_VRBUF_EN = ENABLE;

    ADC_Init(&y);                        //���սṹ��Ĳ�������ADC

		ADC_IE_Enable();                     //ʹ���ж�
    NVIC_Init(NVIC_ADC_IRQn, NVIC_Priority_0, ENABLE);
    ADC_Enable();                        //ʹ��ADC
    ADC_Start();
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

    for (i=0; i<18; i++)
    {
        ADC_Start();

        while(ADC_GetConvStatus() == SET);
        ADC_ClearIFStatus(ADC_IF);

        ad_temp = ADC_GetConvValue();

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
    return sum >>4;
}
