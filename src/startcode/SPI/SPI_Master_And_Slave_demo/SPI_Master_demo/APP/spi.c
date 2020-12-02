/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  SPI主机模块
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "spi.h"

#define Slave_Addr  0x5A

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
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SCK_PIN,&x);        //PA26-SCK,PA27-NSS,PA24-SDO-MOSI   FUN3
    GPIO_Init(GPIOA,SDO_PIN,&x);  
	GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO端口初始化
    
	x.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOA,SDI_PIN,&x);

    y.SPI_Freq = 10000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //接收延时使能
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI初始化
    
    SPI_RecEnable(); 
    SPI_Enable();
}

/*********************************************************
函数名: SPIReadData(uint8_t *rbuf, uint8_t n)
描  述: SPI读数据，连续字节读出(查询模式)
输入值: n—接收数据个数
输出值: rbuf—接收数据缓存
返回值: 无
**********************************************************/
void SPIReadData(uint8_t *rbuf, uint8_t n)
{
    uint16_t i;
    
    CS_RESET; 
    for(i = 0; i < 10; i ++);
    SPI_SendByte(Slave_Addr | 0x01);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    for(i = 0; i < 10; i ++);
    SPI_RX_CLR();  
    for (i = 0; i<n; i++)                
    {
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET); 
        SPI_SendByte(0);  
        while(SPI_GetFlagStatus(SPI_Flag_RB) == RESET);
        rbuf[i] = SPI_RecByte();
    }
    for(i = 0; i < 10; i ++);
    CS_SET;                                      
}

/*********************************************************
函数名: SPIWriteData(uint8_t *wbuf, uint8_t n)
描  述: SPI写数据，连续字节读出(查询模式)
输入值: wbuf：发送的数据
        n—接收数据个数
输出值: 无
返回值: 无
**********************************************************/
void SPIWriteData(uint8_t *wbuf, uint8_t n)
{
    uint16_t i;
    
    CS_RESET; 
    for(i = 0; i < 10; i ++);
    SPI_SendByte(Slave_Addr);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    for(i = 0; i < 10; i ++);
    for (i = 0; i<n; i++)                
    {
        SPI_SendByte(wbuf[i]);  
        while(SPI_GetFlagStatus(SPI_Flag_TB) == RESET);
    }
		while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    for(i = 0; i < 10; i ++);
    CS_SET;                                      
}
