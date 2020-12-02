/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  pwm.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  PWM模块程序头文件
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__

#include "lib_config.h"

void User_T16N2_PWMInit(void);
void PWMOutput(uint16_t temp);

#endif
