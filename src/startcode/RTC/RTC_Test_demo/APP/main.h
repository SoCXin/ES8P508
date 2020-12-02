/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "lib_rtc.h"
#include "systick.h"
#include "light.h"

uint32_t SecondCount = 0;
uint32_t MinuteCount = 0;
uint8_t g_2ms_flag;
uint8_t g_1s_flag;
uint32_t g_1s_cnt;

#endif
