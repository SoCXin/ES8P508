/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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
