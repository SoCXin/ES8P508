/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC主机模块程序
          访问EEPROM
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "iic.h"

/*********************************************************
函数名: void IIC1MasterInit(void)
描  述: IIC主机初始化子程序
输入值: 无
输出值: 无
返回值: 无 
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
    y.I2C_Clk = 300000;        //300KHz
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
函数名: uint8_t IIC1ReadByte(uint8_t slave_addr, uint8_t memory_addr)
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
输出值: 无
返回值: buf—接收数据缓存
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
函数名: void IIC1MasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
描  述: IIC读数据，连续字节读出(查询模式)
输入值: addr—地址
        n—接收数据个数
输出值: buf—接收数据缓存
返回值: 无
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
函数名: ErrorStatus IIC1WriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
输出值: 无
返回值: 无
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
函数名: void IIC1MasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n)
描  述: SPI写数据，逐个字节编程
输入值: addr—地址
        buf—发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
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
函数名: ErrorStatus IIC1MasterErasePage(uint8_t slave_addr, uint8_t memory_addr)
描  述: I2CM擦除页面（填充0xFF），8字节/页
输入值: slave_addr—从机地址
        memory_addr—片内地址
输出值: 无
返回值: 0—TRUE
        1—FALSE
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
