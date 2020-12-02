/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC����ģ�����
          ����EEPROM
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "iic.h"

/*********************************************************
������: void IIC1MasterInit(void)
��  ��: IIC������ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void IICMasterInit(void)
{
    GPIO_InitStruType x;
    I2C_InitStruType y;
	
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Enable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_31,&x);     //PA31--SCL
    GPIO_Init(GPIOA,GPIO_Pin_30,&x);     //PA30--SDA

    y.I2C_SclOd = I2C_PinMode_OD;
    y.I2C_SdaOd = I2C_PinMode_OD;
    y.I2C_16XSamp = DISABLE;
    y.I2C_Clk = 400000;        //400KHz
    y.I2C_Mode = I2C_Mode_Master;
    y.I2C_AutoStop = DISABLE;
    y.I2C_AutoCall = DISABLE;
    I2C_Init(&y);

    I2C_TBIMConfig(I2C_TRBIM_Byte);
    I2C_RBIMConfig(I2C_TRBIM_Byte);
    I2C_RecModeConfig(I2C_RecMode_0);

    I2C_Enable();
}

/*********************************************************
������: uint8_t IIC1ReadByte(uint8_t slave_addr, uint8_t memory_addr)
��  ��: IIC�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: addr����ַ
���ֵ: ��
����ֵ: buf���������ݻ���
**********************************************************/
uint8_t IICReadByte(uint8_t slave_addr, uint8_t memory_addr)
{
    uint8_t i;

    I2C_SendAddress(slave_addr,I2C_Mode_Write);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);

    while(I2C_GetTBStatus() == RESET);
    I2C_SendByte(memory_addr);
    while(I2C_GetTBStatus() == RESET);

    I2C_SendAddress(slave_addr,I2C_Mode_Read);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);

    I2C_RecModeConfig(I2C_RecMode_1);
    I2C_RDTrigger(); 
    while(I2C_GetFlagStatus(I2C_Flag_RB) == RESET);
    i = I2C_RecByte();
    while(I2C_GetFlagStatus(I2C_Flag_RB) == SET);

    I2C_SPTrigger();

    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    return i;
}
/*********************************************************
������: void IIC1MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
��  ��: IIC�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: addr����ַ
        n���������ݸ���
���ֵ: buf���������ݻ���
����ֵ: ��
**********************************************************/
void IICMasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
{
    while(n--)
    {
        *buf = IICReadByte(slave_addr,memory_addr);
        memory_addr++;
        buf++;
    }
}

/*********************************************************
������: ErrorStatus IIC1WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf)
��  ��: SPIд���ݣ�����ֽڱ��
����ֵ: addr����ַ
        buf���������ݻ���
���ֵ: ��
����ֵ: ��
**********************************************************/
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf)
{
    I2C_ClearITPendingBit(I2C_Clr_NA);
    
    I2C_SendAddress(slave_addr,I2C_Mode_Write);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);

    while(I2C_GetTBStatus() == RESET);
    I2C_SendByte(memory_addr);
    while(I2C_GetTBStatus() == RESET);

    I2C_SendByte(buf);
    while(I2C_GetTBStatus() == RESET);

    I2C_SPTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    
    if(I2C_GetFlagStatus(I2C_Flag_NA) == SET)
        return ERROR;
    
    return SUCCESS;
}
/*********************************************************
������: void IIC1MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
��  ��: SPIд���ݣ�����ֽڱ��
����ֵ: addr����ַ
        buf���������ݻ���
        n���������ݸ���
���ֵ: ��
����ֵ: ��
**********************************************************/
void IICMasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
{
    while(n--)
    {
        IICWriteByte(slave_addr,memory_addr,*buf);
        Delay100us(100);
        memory_addr++;
        buf++;
    }
}

/*********************************************************
������: ErrorStatus IIC1MasterErasePage(uint8_t slave_addr, uint8_t memory_addr)
��  ��: I2CM����ҳ�棨���0xFF����8�ֽ�/ҳ
����ֵ: slave_addr���ӻ���ַ
        memory_addr��Ƭ�ڵ�ַ
���ֵ: ��
����ֵ: 0��TRUE
        1��FALSE
**********************************************************/
ErrorStatus IICMasterErasePage(uint8_t slave_addr, uint8_t memory_addr)
{
    uint8_t i;
    
    I2C_ClearITPendingBit(I2C_Clr_NA);

    I2C_SendAddress(slave_addr,I2C_Mode_Write);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);

    while(I2C_GetTBStatus() == RESET);
    I2C_SendByte(memory_addr);
    while(I2C_GetTBStatus() == RESET);

    for (i=0; i<8; i++)
    {
        I2C_SendByte(0xFF);
        while(I2C_GetTBStatus() == RESET);
    }

    I2C_SPTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    
    if(I2C_GetFlagStatus(I2C_Flag_NA) == SET)
        return ERROR;
    
    return SUCCESS;
}
