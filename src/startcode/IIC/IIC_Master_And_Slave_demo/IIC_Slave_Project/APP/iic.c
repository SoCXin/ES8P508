/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC�ӻ�ģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "iic.h"


/*********************************************************
������: void I2C0_SlaveInit(void)
��  ��: IIC�ӻ���ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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
	I2C_CSEnable();           //���ٴ���ʱ���뽫ʱ���Զ�����ʹ��
		
	I2C_SetAddress(SLAVE_ADDR);
	I2C_ITConfig(I2C_IT_SR, ENABLE);
	I2C_ITConfig(I2C_IT_SP, ENABLE);
	NVIC_Init(NVIC_I2C0_IRQn, NVIC_Priority_0, ENABLE);
  
	I2C_Enable();
	
}

/*********************************************************
������: void IIC0_Init(void)
��  ��: IIC�ӻ���ʼ���ӳ�����λ�����
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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
	I2C_CSEnable();           //���ٴ���ʱ���뽫ʱ���Զ�����ʹ��
	
	I2C_ITConfig(I2C_IT_SR, ENABLE);
	I2C_ITConfig(I2C_IT_SP, ENABLE);
	I2C_Enable();
}

