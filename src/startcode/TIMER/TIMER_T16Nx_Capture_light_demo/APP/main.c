/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ��ʱ��CAP��ʾ������ 
      T16Nx��Ӧ�������뷽���źţ��źŷ�����������200Hz����T16Nx���ݲ���״̬�Ͳ����������һ���жϣ�LD1ָʾ�Ʒ�ת
      ע����������������������������������PB4��PB5���˿�ͬʱ����Ϊ��˾ѧϰĸ��AMCUģ���ͨѶ�˿ڣ�ĸ���϶���������
      IO������Ӳ�����������������Դ˴������󲻶ԣ��û����ر�ע�⣬��ͨ��PB6,PB7��PA28,PA29��PB2,PB3����Ķ�ʱ����
      �����ý���ѧϰ����������˾ѧϰ�Ӱ��Դ�LD1��ָʾ�ƣ�����ѧϰ�Ӱ岻���ĸ��������PB4��PB5���˿����벶��Ĺ�
      ��������
*��  ע:  ������ES8P508xоƬ
          ����������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main(void)
{
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    LightInit();
    T16N0CAPInit();                     //PB4,PB5���벶�񣡣��������������뿴ͷ�ļ�˵��
    T16N1CAPInit();                     //PB6,PB7���벶��
    T16N2CAPInit();                     //PA28,PA29���벶��
    T16N3CAPInit();                     //PB2,PB3���벶��

    GPIOA_SetBit(GPIO_Pin_14);          //ʹ��LD1ָʾ����״̬
    GPIOA_SetBit(GPIO_Pin_13);
    GPIOA_SetBit(GPIO_Pin_12);      
    GPIOA_SetBit(GPIO_Pin_11);
    while(1);
}
