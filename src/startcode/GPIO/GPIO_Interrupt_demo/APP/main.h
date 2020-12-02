/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "led.h"
#include "timer.h"
#include "irqhandler.h"

uint8_t g_2ms_flag;
uint8_t g_10ms_flag;
uint32_t g_10ms_cnt;
uint8_t g_1s_flag;
uint32_t g_1s_cnt;
uint8_t g_led_buf[4];
uint8_t g_key_flag_4;

#endif
