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
    GPIO_Init(GPIOA,SCK_PIN,&x);        // PA26-SCK,PA27-NSS,PA25-SDI-MISO,PA24-SDO-MOSI    FUN3
    GPIO_Init(GPIOA,SDI_PIN,&x);
    GPIO_Init(GPIOA,SDO_PIN,&x);

	x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO端口初始化

    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_FallSendRiseRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //接收延时使能
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI初始化

    SPI_Enable();
}

/*********************************************************
函数名: void SPI_Ewen(void)
描  述: EEPROM写使能
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void SPI_Ewen(void)
{
    CS_SET;                             //拉高片选信号
    SPI_SendByte(0x02);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(0x60);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    CS_RESET;
}

/*********************************************************
函数名: void SPI_Ewds(void)
描  述: EEPROM写禁止
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void SPI_Ewds(void)
{
    CS_SET;    //cs
    SPI_SendByte(0x02);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(0x00);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    CS_RESET;
}

/*********************************************************
函数名: void SPIReadData(uchar addr, uchar *buf, uchar n)
描  述: SPI读数据，连续字节读出(查询模式)
输入值: addr—地址
        n—接收数据个数
输出值: buf—接收数据缓存
返回值: 无
**********************************************************/
void SPIReadData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;

    CS_SET;                                             //cs

    SPI_SendByte(0x03);                                 //指令
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(addr);                                 //地址
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);

    SPI_RecEnable();                                    //使能接收

    for (i = 0; i<n; i++)                               //接收
    {
        while(SPI_GetFlagStatus(SPI_Flag_RB));          //缓存器空时才接收
        SPI_SendByte(0);                                //发送接收用的时钟
        while(SPI_GetFlagStatus(SPI_Flag_RB) == RESET);
        buf[i] = SPI_RecByte();
    }

    CS_RESET;                                           //cs

    SPI_RecDisable();                                   //禁止接收
}

/*********************************************************
函数名: uchar SPIWriteData(uchar memory_addr, uchar *buf, uchar n)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
**********************************************************/
void SPIWriteData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;
    GPIO_InitStruType x; 

	  x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PDEN = GPIO_PDE_Input_Enable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                            //MISO设为输入，用来判断响应

    SPI_Ewen();                                             //dis写保护
    Delay100us(1);

    for (i = 0; i < n; i++)
    {
        CS_SET;

        SPI_SendByte(0x02);                                 //指令
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        SPI_SendByte(0x80|(addr+i));                        //地址
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        SPI_SendByte(buf[i]);                               //数据
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        Delay100us(1);

        CS_RESET;
        CS_RESET;                                   //拉低片选，触发编程
        CS_SET;
        Delay100us(1);

        while(GPIO_ReadBit(GPIOA,SDI_PIN) == 0);   //等到MISO被拉高

        CS_RESET;                                  //操作完成，cs失能
    }

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                            //数据口重设为spi

    Delay100us(1);
    SPI_Ewds();                                             //写保护
}

/*********************************************************
函数名: void SPIEraseAll(void)
描  述: SPI擦除全片（填充0xFF）
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void SPIEraseAll(void)
{
    GPIO_InitStruType x;

	  x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PDEN = GPIO_PDE_Input_Enable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                        //MISO设为输入，用来判断响应

    SPI_Ewen();                                         //dis写保护
    Delay100us(1);

    CS_SET;
    SPI_SendByte(0x02);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(0x40);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);

    CS_RESET;
    CS_RESET;                                          //拉低片选，触发编程
    CS_SET;
    Delay100us(1);

    while(GPIO_ReadBit(GPIOA,SDI_PIN) == 0);   //等到MISO被拉高

    CS_RESET;                                           //操作完成，cs失能

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                        //数据口重设为spi

    Delay100us(1);
    SPI_Ewds();                                         //写保护
}

