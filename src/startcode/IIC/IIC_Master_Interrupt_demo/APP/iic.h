/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  iic.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  IIC主机模块头文件
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"
#include "systick.h"

extern uint8_t g_txbuf[0xFF];          //发送数据缓存
extern uint8_t g_tx_length;            //发送数据长度
extern uint8_t g_tx_count;             //发送字节计数

extern uint8_t g_rxbuf[0xFF];          //接收数据缓存
extern uint8_t g_rx_length;            //接收数据长度
extern uint8_t g_rx_count;             //接收字节计数

void IICMasterInit(void);
uint8_t IICReadByte(uint8_t slave_addr, uint8_t memory_addr);
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf);
void IICMasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
void IICMasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
ErrorStatus IICMasterErasePage(uint8_t slave_addr, uint8_t memory_addr);

#endif
