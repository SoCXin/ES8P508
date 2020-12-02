/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  IIC从机演示主程序
          采用辅助AMCU作为主机，周期读取本机设置的数据，并回送给本机。
          按键修改本机要发送的数据（1字节），同时本机接收主机数据，通过LED数码管前两位显示，后两位显示本机设置数据
          （1）单击K5：发送数据+1
          基本协议：从机地址（0x5A）+片内地址（0x01）+单字节数据
          中断方式处理通讯
		      本演示demo需要将AMCU的4号拨码推上去
		      需要将主机母板IIC主设备SCL接到 PA31 ，SDA接到PA30
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#define COMMOND1    0x01    //内部地址（可扩展为命令或功能码）

uint8_t iic_status;         //I2C通讯状态机
uint8_t iic_restart;        //RESTART标志
uint8_t temp_buf;
uint8_t wbuf;
uint8_t rbuf;

uint8_t data;         //读写数据
uint8_t data_h;       //读写数据高半字节（显示位于led_buf[2]）
uint8_t data_l;       //读写数据低半字节（显示位于led_buf[3]）

uint8_t g_key_cmd;
uint8_t flag;
uint8_t com;
uint8_t g_led_buf[4];    //显示缓存

int main(void)
{
	SystemClockConfig();                                                //配置时钟  
	DeviceClockAllEnable();                                             //打开所有外设时钟

	SysTickInit();
	T16N3Init();
	LEDInit();
	KeyInit();
	I2C0_SlaveInit();
	
	g_2ms_flag  = 0;
	g_10ms_flag = 0;
	g_2ms_cnt   = 0;
	g_key_cmd   = 0;
	flag        = 0;
	com         = 0;		//初始化显示位
  
	data_h = 0x00;            	//初始化数据
	data_l = 0x00;
	data = (data_h << 4) + data_l;
	
	while(1)
	{
		if (g_2ms_flag == 1) {                   	//判断2ms标志（LED显示刷新周期）
			g_2ms_flag = 0;                       	//标志清0
			LEDDisplayData(com, g_led_buf[com]);    //刷新LED显示数据
			com++;                                	//显示位+1
			if (com > 3)                            //显示位0~3
				com = 0;
		}	

		if (g_10ms_flag == 1) {
			g_10ms_flag = 0;
			g_key_cmd = KeyGetValue();

			switch (g_key_cmd) {
                case 1:
				data++;
				if(data>=0xff)
					data =0;
				rbuf = data;
				break;
			default:
				g_key_cmd = 0;
				break;
			}

			data_l = rbuf  & 0x0F;		//更新读出数据
			data_h = (rbuf & 0xFF) >> 4;

			g_led_buf[0] = (wbuf >> 4);			//更新显示缓存
			g_led_buf[1] = (wbuf & 0x0f);
			g_led_buf[2] = data_h;
			g_led_buf[3] = data_l;
		}
	}
}

/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{
	if(I2C_GetITStatus(I2C_IT_SR) == SET) {		//收到起始位+地址匹配+发送应答位
		I2C_ClearITPendingBit(I2C_Clr_SR);		//清I2C起始位+地址匹配+发送应答位标志位            
		if(I2C_GetRWMode() == I2C_Mode_Read) {   	//主机读
			I2C_ITConfig(I2C_IT_RB, DISABLE);
			I2C_ITConfig(I2C_IT_TB, ENABLE);
			iic_restart = 1;    			//置RESTART标志，准备读取首字节
		}
		else if(I2C_GetRWMode()==I2C_Mode_Write) {   //主机写
			I2C_ITConfig(I2C_IT_TB, DISABLE);
			I2C_ITConfig(I2C_IT_RB, ENABLE);
			iic_status = 1;     			//I2C总线状态：接收片内地址
		}     
	}

	if(I2C_GetITStatus(I2C_IT_RB)==SET) {		//I2C接收缓冲器有接收数据
		temp_buf = I2C_RecByte();   		//读接收缓冲器，硬件清接收中断标志  
		if(iic_status == 1) {
			if(temp_buf == COMMOND1)    		//判断片内地址（命令）正确
				iic_status = 2;         	//I2C总线状态：接收数据内容
			else
				iic_status = 0;             	//I2C总线状态：初始等待
		}
		else if(iic_status == 2) {
			wbuf = temp_buf;     			//保存接收数据
		}
		else
			iic_status = 0;             		//I2C总线状态：初始等待
	}

	if(I2C_GetITStatus(I2C_IT_TB)==SET) {  		//I2C发送缓冲器未满标志
		if(iic_restart) {
			I2C_SendByte(rbuf);    		//写发送缓冲器，首字节
			iic_restart = 0;                  	//清RESTART标志
		}
		else {
			I2C_SendByte(rbuf);    		//写发送缓冲器，后续字节 
		}           
	}

	if(I2C_GetITStatus(I2C_IT_SP)==SET) {		//收到结束位
		I2C_ClearITPendingBit(I2C_Clr_SP);  	//清结束位中断标志     
		I2C_Reset();        				//I2C模块复位
		I2C0_Init();       				//再次初始化
		iic_status = 0;    				//I2C总线状态：初始等待
	}
}
