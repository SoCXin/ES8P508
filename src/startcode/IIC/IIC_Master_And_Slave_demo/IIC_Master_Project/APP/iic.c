/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC����ģ�����
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
    x.GPIO_DS = GPIO_DS_Output_Strong;
	  GPIO_Init(GPIOA,GPIO_Pin_31,&x);     //PA31--SCL,FUN3
	  GPIO_Init(GPIOA,GPIO_Pin_30,&x);     //PA30--SDA,FUN3
	
    y.I2C_SclOd = I2C_PinMode_OD;
    y.I2C_SdaOd = I2C_PinMode_OD;
    y.I2C_16XSamp = DISABLE;
    y.I2C_Clk = 10000;        //10KHz
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
������: uint8_t IICReadByte(uint8_t slave_addr)
��  ��: IIC�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: slave_addr����ַ
���ֵ: ��
����ֵ: buf���������ݻ���
**********************************************************/
uint8_t IICReadByte(uint8_t slave_addr)
{
    uint8_t i;
	
    I2C_SendAddress(slave_addr,I2C_Mode_Read);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SR);

    I2C_RecModeConfig(I2C_RecMode_1);
    I2C_RDTrigger(); 	
    while(I2C_GetFlagStatus(I2C_Flag_RB) == RESET);
    i = I2C_RecByte();
    while(I2C_GetFlagStatus(I2C_Flag_RB) == SET);


    I2C_SPTrigger();

    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SP);
	
    return i;
}

/*********************************************************
������: ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf)
��  ��: IICд���ݣ�����ֽڱ��
����ֵ: addr����ַ
        buf���������ݻ���
���ֵ: ��
����ֵ: ��
**********************************************************/
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t buf)
{
    I2C_ClearITPendingBit(I2C_Clr_NA);
    
    I2C_SendAddress(slave_addr,I2C_Mode_Write);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SR);

    while(I2C_GetTBStatus() == RESET);

    I2C_SendByte(buf);
    while(I2C_GetTBStatus() == RESET);

    I2C_SPTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SP);
    
    if(I2C_GetFlagStatus(I2C_Flag_NA) == SET)
        return ERROR;
    
    return SUCCESS;
}



/*********************************************************
������: void IICReadBuf(uint8_t slave_addr , char * buf, char size )
��  ��: IIC�����ݣ������ֽڶ���(��ѯģʽ)
����ֵ: slave_addr����ַ
        size-�������ݴ�С
���ֵ: ��
����ֵ: buf���������ݻ���
**********************************************************/
void IICReadBuf(uint8_t slave_addr , char * buf, char size )
{
    I2C_SendAddress(slave_addr,I2C_Mode_Read);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SR);

    I2C_RecModeConfig(I2C_RecMode_0);
    while(size-->1)
    {
        I2C_RDTrigger(); 	
        while(I2C_GetFlagStatus(I2C_Flag_RB) == RESET);
        *buf++ = I2C_RecByte();
    }

	I2C_RecModeConfig(I2C_RecMode_1);
	I2C_RDTrigger(); 	
	while(I2C_GetFlagStatus(I2C_Flag_RB) == RESET);
	*buf = I2C_RecByte();

    while(I2C_GetFlagStatus(I2C_Flag_RB) == SET);


    I2C_SPTrigger();

    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SP);
}




/*********************************************************
������: IICWriteBuf
��  ��: IIC����д����
����ֵ: addr����ַ
        buf���������ݻ���
        size-�������ݴ�С
���ֵ: ��
����ֵ: ��
**********************************************************/
ErrorStatus IICWriteBuf(uint8_t slave_addr, char * buf,char size)
{
    I2C_ClearITPendingBit(I2C_Clr_NA);
    
    I2C_SendAddress(slave_addr,I2C_Mode_Write);
    I2C_SRTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SR) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SR);

    while(size-- > 0)
    {
        while(I2C_GetTBStatus() == RESET);
        I2C_SendByte(*buf++);
    }
	
    while(I2C_GetTBStatus() == RESET);

    I2C_SPTrigger();
    while(I2C_GetFlagStatus(I2C_Flag_SP) == RESET);
    I2C_ClearITPendingBit(I2C_Clr_SP);
    
    if(I2C_GetFlagStatus(I2C_Flag_NA) == SET)
        return ERROR;
    
    return SUCCESS;
}
