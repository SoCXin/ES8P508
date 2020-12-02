/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  SPI����ģ��
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "spi.h"

#define Slave_Addr  0x5A

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
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SCK_PIN,&x);        //PA26-SCK,PA27-NSS,PA24-SDO-MOSI   FUN3
    GPIO_Init(GPIOA,SDO_PIN,&x);  
	GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO�˿ڳ�ʼ��
    
	x.GPIO_Direction = GPIO_Dir_In;
    GPIO_Init(GPIOA,SDI_PIN,&x);

    y.SPI_Freq = 10000;
    y.SPI_Df = SPI_RiseSendFallRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //������ʱʹ��
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI��ʼ��
    
    SPI_RecEnable(); 
    SPI_Enable();
}

/*********************************************************
������: SPIReadData(uint8_t *rbuf, uint8_t n)
��  ��: SPI�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: n���������ݸ���
���ֵ: rbuf���������ݻ���
����ֵ: ��
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
������: SPIWriteData(uint8_t *wbuf, uint8_t n)
��  ��: SPIд���ݣ������ֽڶ���(��ѯģʽ)
����ֵ: wbuf�����͵�����
        n���������ݸ���
���ֵ: ��
����ֵ: ��
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
