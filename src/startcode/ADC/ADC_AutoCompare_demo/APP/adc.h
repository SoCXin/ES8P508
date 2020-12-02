/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  adc.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  ADCģ�����ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "lib_config.h"

extern uint16_t g_adc_buf[18];

void ADC0_UserInit(void);
void ADCACPConfig(void);
uint16_t ADCRead(void);

#endif
