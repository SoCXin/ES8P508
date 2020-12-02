/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC从机模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "iic.h"


/*********************************************************
函数名: void I2C0_SlaveInit(void)
描  述: IIC从机初始化子程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void I2C0_SlaveInit(void)
{
	GPIO_InitStruType x;
	I2C_InitStruType y;
	
	//IIC0 PA30,31
	x.GPIO_Signal = GPIO_Pin_Signal_Digital;
	x.GPIO_Func = GPIO_Func_3;
	x.GPIO_Direction = GPIO_Dir_Out;
  x.GPIO_PUEN = GPIO_PUE_Input_Enable;
  x.GPIO_PDEN = GPIO_PDE_Input_Disable;
  x.GPIO_OD = GPIO_ODE_Output_Enable;
	x.GPIO_DS = GPIO_DS_Output_Strong;
	GPIO_Init(GPIOA,GPIO_Pin_31,&x);     //PA31--SCL
	GPIO_Init(GPIOA,GPIO_Pin_30,&x);     //PA30--SDA
	
	y.I2C_16XSamp = DISABLE;
	y.I2C_Mode = I2C_Mode_Slave;
	y.I2C_SclOd = I2C_PinMode_OD;
	y.I2C_SdaOd = I2C_PinMode_OD;
	y.I2C_AutoStop = DISABLE;
	y.I2C_AutoCall = DISABLE;
	y.I2C_Clk = 10000;        //10KHz
	
	I2C_Init(&y);
	I2C_CSEnable();           //高速传输时必须将时钟自动下拉使能
		
	I2C_SetAddress(SLAVE_ADDR);
	I2C_ITConfig(I2C_IT_SR, ENABLE);
	I2C_ITConfig(I2C_IT_SP, ENABLE);
	NVIC_Init(NVIC_I2C0_IRQn, NVIC_Priority_0, ENABLE);
  
	I2C_Enable();
	
}

/*********************************************************
函数名: void IIC0_Init(void)
描  述: IIC从机初始化子程序，软复位后调用
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void I2C0_Init(void)
{
	I2C_InitStruType y;
	y.I2C_16XSamp = DISABLE;
	y.I2C_Mode = I2C_Mode_Slave;
	y.I2C_SclOd = I2C_PinMode_OD;
	y.I2C_SdaOd = I2C_PinMode_OD;
	y.I2C_AutoStop = DISABLE;
	y.I2C_AutoCall = DISABLE;
	y.I2C_Clk = 10000;        //10KHz
	
	I2C_Init(&y);
	I2C_CSEnable();           //高速传输时必须将时钟自动下拉使能
	
	I2C_ITConfig(I2C_IT_SR, ENABLE);
	I2C_ITConfig(I2C_IT_SP, ENABLE);
	I2C_Enable();
}

