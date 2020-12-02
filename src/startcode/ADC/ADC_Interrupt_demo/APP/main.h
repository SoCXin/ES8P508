/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  
*��  ע:  ������HRSDK-GDB-ES8P508 V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "adc.h"
#include "key.h"
#include "led.h"
#include "systick.h"
#include "timer.h"

#define  VREF	3.3	
#define  RATION VREF/4096 * 1000

uint8_t g_2ms_flag;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint16_t g_200ms_flag;
uint16_t g_200ms_cnt;
uint16_t g_adc_data;
uint8_t g_adc_flag;

#endif

