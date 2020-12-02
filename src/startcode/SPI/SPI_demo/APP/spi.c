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
    GPIO_Init(GPIOA,CS_PIN,&x);         //GPIO�˿ڳ�ʼ��

    y.SPI_Freq = 80000;
    y.SPI_Df = SPI_FallSendRiseRec;
    y.SPI_Mode = SPI_Mode_Master;
    y.SPI_DW = 7;
    y.SPI_DelayRec = ENABLE;            //������ʱʹ��
    y.SPI_DelaySend = DISABLE;
    y.SPI_SendDelayPeroid = 0;
    SPI_Init(&y);                       //SPI��ʼ��

    SPI_Enable();
}

/*********************************************************
������: void SPI_Ewen(void)
��  ��: EEPROMдʹ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void SPI_Ewen(void)
{
    CS_SET;                             //����Ƭѡ�ź�
    SPI_SendByte(0x02);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(0x60);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    CS_RESET;
}

/*********************************************************
������: void SPI_Ewds(void)
��  ��: EEPROMд��ֹ
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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
������: void SPIReadData(uchar addr, uchar *buf, uchar n)
��  ��: SPI�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: addr����ַ
        n���������ݸ���
���ֵ: buf���������ݻ���
����ֵ: ��
**********************************************************/
void SPIReadData(uint8_t addr, uint8_t *buf, uint8_t n)
{
    uint8_t i;

    CS_SET;                                             //cs

    SPI_SendByte(0x03);                                 //ָ��
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(addr);                                 //��ַ
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);

    SPI_RecEnable();                                    //ʹ�ܽ���

    for (i = 0; i<n; i++)                               //����
    {
        while(SPI_GetFlagStatus(SPI_Flag_RB));          //��������ʱ�Ž���
        SPI_SendByte(0);                                //���ͽ����õ�ʱ��
        while(SPI_GetFlagStatus(SPI_Flag_RB) == RESET);
        buf[i] = SPI_RecByte();
    }

    CS_RESET;                                           //cs

    SPI_RecDisable();                                   //��ֹ����
}

/*********************************************************
������: uchar SPIWriteData(uchar memory_addr, uchar *buf, uchar n)
��  ��: SPIд���ݣ�����ֽڱ��
����ֵ: addr����ַ
        buf���������ݻ���
        n���������ݸ���
���ֵ: ��
����ֵ: ��
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
    GPIO_Init(GPIOA,SDI_PIN,&x);                            //MISO��Ϊ���룬�����ж���Ӧ

    SPI_Ewen();                                             //disд����
    Delay100us(1);

    for (i = 0; i < n; i++)
    {
        CS_SET;

        SPI_SendByte(0x02);                                 //ָ��
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        SPI_SendByte(0x80|(addr+i));                        //��ַ
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        SPI_SendByte(buf[i]);                               //����
        while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
        Delay100us(1);

        CS_RESET;
        CS_RESET;                                   //����Ƭѡ���������
        CS_SET;
        Delay100us(1);

        while(GPIO_ReadBit(GPIOA,SDI_PIN) == 0);   //�ȵ�MISO������

        CS_RESET;                                  //������ɣ�csʧ��
    }

		x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                            //���ݿ�����Ϊspi

    Delay100us(1);
    SPI_Ewds();                                             //д����
}

/*********************************************************
������: void SPIEraseAll(void)
��  ��: SPI����ȫƬ�����0xFF��
����ֵ: ��
���ֵ: ��
����ֵ: ��
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
    GPIO_Init(GPIOA,SDI_PIN,&x);                        //MISO��Ϊ���룬�����ж���Ӧ

    SPI_Ewen();                                         //disд����
    Delay100us(1);

    CS_SET;
    SPI_SendByte(0x02);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);
    SPI_SendByte(0x40);
    while(SPI_GetFlagStatus(SPI_Flag_IDLE) == RESET);

    CS_RESET;
    CS_RESET;                                          //����Ƭѡ���������
    CS_SET;
    Delay100us(1);

    while(GPIO_ReadBit(GPIOA,SDI_PIN) == 0);   //�ȵ�MISO������

    CS_RESET;                                           //������ɣ�csʧ��

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,SDI_PIN,&x);                        //���ݿ�����Ϊspi

    Delay100us(1);
    SPI_Ewds();                                         //д����
}

