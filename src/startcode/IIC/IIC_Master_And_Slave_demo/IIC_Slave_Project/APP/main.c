/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  IIC主从机通信程序，本程序为从机程序，负责接收主机发来的数据，并保存起来。下次主机读的时候，发送保存的数据。
          主机从机需要连接SCL（PA31）和SDA（PA30），并上拉。
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

#include "iic.h"

int main()
{
	
	SystemClockConfig();                //配置时钟  
	DeviceClockAllEnable();             //打开所有外设时钟
	I2C0_SlaveInit();
	while(1)
	{
		
	}
	
}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
char iic_buf[8];
char buf_count =0;
void I2C0_IRQHandler(void)
{
	
	if(I2C_GetITStatus(I2C_IT_SR) == SET) {		//收到起始位+地址匹配+发送应答位
		I2C_ClearITPendingBit(I2C_Clr_SR);		//清I2C起始位+地址匹配+发送应答位标志位            
		if(I2C_GetRWMode() == I2C_Mode_Read) {   	//主机读
			I2C_ITConfig(I2C_IT_RB, DISABLE);
			
            I2C_ClearITPendingBit(I2C_Clr_NA);
            I2C_ClearITPendingBit(I2C_Clr_TIDLE);
            I2C_ITConfig(I2C_IT_TIDLE, ENABLE);
            
			buf_count = 0;
            I2C_SendByte(iic_buf[buf_count++]);    		//写发送缓冲
		}
		else if(I2C_GetRWMode()==I2C_Mode_Write) {   //主机写
			I2C_ITConfig(I2C_IT_TIDLE, DISABLE);
			I2C_ITConfig(I2C_IT_RB, ENABLE);
			buf_count = 0;
		}     
	}

	if(I2C_GetITStatus(I2C_IT_RB)==SET) {		//I2C接收缓冲器有接收数据
		
		iic_buf[buf_count++] = I2C_RecByte();   		//读接收缓冲器，硬件清接收中断标志  
	}

	if(I2C_GetITStatus(I2C_IT_TIDLE)==SET) {      //I2C空闲
		I2C_ClearITPendingBit(I2C_Clr_TIDLE);
        if(I2C_GetFlagStatus(I2C_Flag_NA) != SET){        //没有接收到NACK
            I2C_SendByte(iic_buf[buf_count++]);    		//写发送缓冲器 
        }
	}

	if(I2C_GetITStatus(I2C_IT_SP)==SET) {		//收到结束位
		I2C_ClearITPendingBit(I2C_Clr_SP);  	//清结束位中断标志     
		I2C_ITConfig(I2C_IT_TIDLE, DISABLE);
		I2C_ITConfig(I2C_IT_RB, DISABLE);
        I2C_ClearITPendingBit(I2C_Clr_NA);
		buf_count = 0;
	}
}




