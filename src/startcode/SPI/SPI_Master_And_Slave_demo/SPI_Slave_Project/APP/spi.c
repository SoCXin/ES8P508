/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  SPI从机模块
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"


/*********************************************************
函数名: void SPI_GPIO_Init(void)
描  述: SPI_GPIO初始化
输入值: 无
输出值: 无
返回值: 无 
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
    GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO端口初始化
    
    x.GPIO_Direction = GPIO_Dir_Out;
    GPIO_Init(GPIOA,SDO_PIN,&x);
    
    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Slave;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //接收延时使能
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI初始化
    
    SPI_ITConfig(SPI_IT_NSS, ENABLE);
    NVIC_Init(NVIC_SPI0_IRQn, NVIC_Priority_0, ENABLE);
    
    SPI_RecEnable(); 
    SPI_Enable();
}



