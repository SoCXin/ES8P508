/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  SPI�ӻ�ģ��
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "spi.h"


/*********************************************************
������: void SPI_GPIO_Init(void)
��  ��: SPI_GPIO��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void SPI_GPIO_Init(void)
{
    GPIO_InitStruType x;
    SPI_InitStruType y;

	  x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SCK_PIN,&x);        //PA26-SCK,PA27-NSS,PA24-SDO-MOSI    FUN3
    GPIO_Init(GPIOA,SDI_PIN,&x);
    GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO�˿ڳ�ʼ��
    
    x.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOA,SDO_PIN,&x);
    
    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Slave;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //������ʱʹ��
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI��ʼ��
    
    SPI_ITConfig(SPI_IT_NSS, ENABLE);
    NVIC_Init(NVIC_SPI0_IRQn, NVIC_Priority_0, ENABLE);
    
    SPI_RecEnable(); 
    SPI_Enable();
}



