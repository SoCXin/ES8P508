/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  IIC���ӻ�ͨ�ų��򣬱�����Ϊ�ӻ����򣬸�������������������ݣ��������������´���������ʱ�򣬷��ͱ�������ݡ�
          �����ӻ���Ҫ����SCL��PA31����SDA��PA30������������
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/

#include "iic.h"

int main()
{
	
	SystemClockConfig();                //����ʱ��  
	DeviceClockAllEnable();             //����������ʱ��
	I2C0_SlaveInit();
	while(1)
	{
		
	}
	
}

/***************************************************************
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
char iic_buf[8];
char buf_count =0;
void I2C0_IRQHandler(void)
{
	
	if(I2C_GetITStatus(I2C_IT_SR) == SET) {		//�յ���ʼλ+��ַƥ��+����Ӧ��λ
		I2C_ClearITPendingBit(I2C_Clr_SR);		//��I2C��ʼλ+��ַƥ��+����Ӧ��λ��־λ            
		if(I2C_GetRWMode() == I2C_Mode_Read) {   	//������
			I2C_ITConfig(I2C_IT_RB, DISABLE);
			
            I2C_ClearITPendingBit(I2C_Clr_NA);
            I2C_ClearITPendingBit(I2C_Clr_TIDLE);
            I2C_ITConfig(I2C_IT_TIDLE, ENABLE);
            
			buf_count = 0;
            I2C_SendByte(iic_buf[buf_count++]);    		//д���ͻ���
		}
		else if(I2C_GetRWMode()==I2C_Mode_Write) {   //����д
			I2C_ITConfig(I2C_IT_TIDLE, DISABLE);
			I2C_ITConfig(I2C_IT_RB, ENABLE);
			buf_count = 0;
		}     
	}

	if(I2C_GetITStatus(I2C_IT_RB)==SET) {		//I2C���ջ������н�������
		
		iic_buf[buf_count++] = I2C_RecByte();   		//�����ջ�������Ӳ��������жϱ�־  
	}

	if(I2C_GetITStatus(I2C_IT_TIDLE)==SET) {      //I2C����
		I2C_ClearITPendingBit(I2C_Clr_TIDLE);
        if(I2C_GetFlagStatus(I2C_Flag_NA) != SET){        //û�н��յ�NACK
            I2C_SendByte(iic_buf[buf_count++]);    		//д���ͻ����� 
        }
	}

	if(I2C_GetITStatus(I2C_IT_SP)==SET) {		//�յ�����λ
		I2C_ClearITPendingBit(I2C_Clr_SP);  	//�����λ�жϱ�־     
		I2C_ITConfig(I2C_IT_TIDLE, DISABLE);
		I2C_ITConfig(I2C_IT_RB, DISABLE);
        I2C_ClearITPendingBit(I2C_Clr_NA);
		buf_count = 0;
	}
}




