/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  spi.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  SPI主机模块头文件
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "ES8P508x.h"
#include "lib_config.h"
#include "lib_spi.h"

#define Slave_Addr  0x5A

#define CS_SET GPIOA_SetBit(GPIO_Pin_27)
#define CS_RESET GPIOA_ResetBit(GPIO_Pin_27)
#define SCK_PIN GPIO_Pin_26
#define CS_PIN  GPIO_Pin_27
#define SDI_PIN GPIO_Pin_25
#define SDO_PIN GPIO_Pin_24

/* 函数声明 */
void SPI_GPIO_Init(void);

#endif
