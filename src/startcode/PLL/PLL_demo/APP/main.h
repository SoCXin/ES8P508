/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  
*备  注:  适用于HRSDK-GDB-ES8P508x
          本软件仅供学习和演示使用，对用户直接引用代码
		  所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "lib_config.h"
#include "timer.h"
#include "light.h"

uint8_t g_2ms_flag;
uint8_t g_10ms_flag;
uint8_t g_10ms_cnt;
uint32_t g_900ms_flag;
uint32_t g_900ms_cnt;

#endif
