/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  IIC�ӻ���ʾ������
          ���ø���AMCU��Ϊ���������ڶ�ȡ�������õ����ݣ������͸�������
          �����޸ı���Ҫ���͵����ݣ�1�ֽڣ���ͬʱ���������������ݣ�ͨ��LED�����ǰ��λ��ʾ������λ��ʾ������������
          ��1������K5����������+1
          ����Э�飺�ӻ���ַ��0x5A��+Ƭ�ڵ�ַ��0x01��+���ֽ�����
          �жϷ�ʽ����ͨѶ
		      ����ʾdemo��Ҫ��AMCU��4�Ų�������ȥ
		      ��Ҫ������ĸ��IIC���豸SCL�ӵ� PA31 ��SDA�ӵ�PA30
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#define COMMOND1    0x01    //�ڲ���ַ������չΪ��������룩

uint8_t iic_status;         //I2CͨѶ״̬��
uint8_t iic_restart;        //RESTART��־
uint8_t temp_buf;
uint8_t wbuf;
uint8_t rbuf;

uint8_t data;         //��д����
uint8_t data_h;       //��д���ݸ߰��ֽڣ���ʾλ��led_buf[2]��
uint8_t data_l;       //��д���ݵͰ��ֽڣ���ʾλ��led_buf[3]��

uint8_t g_key_cmd;
uint8_t flag;
uint8_t com;
uint8_t g_led_buf[4];    //��ʾ����

int main(void)
{
	SystemClockConfig();                                                //����ʱ��  
	DeviceClockAllEnable();                                             //����������ʱ��

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
	com         = 0;		//��ʼ����ʾλ
  
	data_h = 0x00;            	//��ʼ������
	data_l = 0x00;
	data = (data_h << 4) + data_l;
	
	while(1)
	{
		if (g_2ms_flag == 1) {                   	//�ж�2ms��־��LED��ʾˢ�����ڣ�
			g_2ms_flag = 0;                       	//��־��0
			LEDDisplayData(com, g_led_buf[com]);    //ˢ��LED��ʾ����
			com++;                                	//��ʾλ+1
			if (com > 3)                            //��ʾλ0~3
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

			data_l = rbuf  & 0x0F;		//���¶�������
			data_h = (rbuf & 0xFF) >> 4;

			g_led_buf[0] = (wbuf >> 4);			//������ʾ����
			g_led_buf[1] = (wbuf & 0x0f);
			g_led_buf[2] = data_h;
			g_led_buf[3] = data_l;
		}
	}
}

/***************************************************************
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void I2C0_IRQHandler(void)
{
	if(I2C_GetITStatus(I2C_IT_SR) == SET) {		//�յ���ʼλ+��ַƥ��+����Ӧ��λ
		I2C_ClearITPendingBit(I2C_Clr_SR);		//��I2C��ʼλ+��ַƥ��+����Ӧ��λ��־λ            
		if(I2C_GetRWMode() == I2C_Mode_Read) {   	//������
			I2C_ITConfig(I2C_IT_RB, DISABLE);
			I2C_ITConfig(I2C_IT_TB, ENABLE);
			iic_restart = 1;    			//��RESTART��־��׼����ȡ���ֽ�
		}
		else if(I2C_GetRWMode()==I2C_Mode_Write) {   //����д
			I2C_ITConfig(I2C_IT_TB, DISABLE);
			I2C_ITConfig(I2C_IT_RB, ENABLE);
			iic_status = 1;     			//I2C����״̬������Ƭ�ڵ�ַ
		}     
	}

	if(I2C_GetITStatus(I2C_IT_RB)==SET) {		//I2C���ջ������н�������
		temp_buf = I2C_RecByte();   		//�����ջ�������Ӳ��������жϱ�־  
		if(iic_status == 1) {
			if(temp_buf == COMMOND1)    		//�ж�Ƭ�ڵ�ַ�������ȷ
				iic_status = 2;         	//I2C����״̬��������������
			else
				iic_status = 0;             	//I2C����״̬����ʼ�ȴ�
		}
		else if(iic_status == 2) {
			wbuf = temp_buf;     			//�����������
		}
		else
			iic_status = 0;             		//I2C����״̬����ʼ�ȴ�
	}

	if(I2C_GetITStatus(I2C_IT_TB)==SET) {  		//I2C���ͻ�����δ����־
		if(iic_restart) {
			I2C_SendByte(rbuf);    		//д���ͻ����������ֽ�
			iic_restart = 0;                  	//��RESTART��־
		}
		else {
			I2C_SendByte(rbuf);    		//д���ͻ������������ֽ� 
		}           
	}

	if(I2C_GetITStatus(I2C_IT_SP)==SET) {		//�յ�����λ
		I2C_ClearITPendingBit(I2C_Clr_SP);  	//�����λ�жϱ�־     
		I2C_Reset();        				//I2Cģ�鸴λ
		I2C0_Init();       				//�ٴγ�ʼ��
		iic_status = 0;    				//I2C����״̬����ʼ�ȴ�
	}
}
