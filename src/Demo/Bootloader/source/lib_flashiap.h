/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  lib_flashiap.h
*作  者:
*版  本:  V1.00
*日  期:  2015/12/03
*描  述:  FlashIAP库函数头文件
*备  注:  适用于HRSDK-GDB-8P506
         本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __LIBIAP_H__
#define __LIBIAP_H__

#include "ES8P508x.h"


/* IAP Function */
uint8_t EraseAll(void) ;

/* 寄存器解锁 */
#define FlashIAP_RegUnLock() (IAP->UL.UL = 0x49415055)
#define FlashIAP_RegLock()   (IAP->UL.UL = 0x00000000)

/* 使能IAP */
#define FlashIAP_Enable()  (IAP->CON.EN = 0x1)
#define FlashIAP_Disable() (IAP->CON.EN = 0x0)


typedef uint32_t (*iap_pageerase_t)(uint32_t);
#define  IAP_PageErase  ((iap_pageerase_t)(*((uint32_t *)0x10000000)))

typedef uint32_t (*iap_wordprogrm_t)(uint32_t, uint32_t);
#define  IAP_WordProgram  ((iap_wordprogrm_t)(*((uint32_t *)0x10000004)))

typedef uint32_t (*iap_wordsprogrm_t)(uint32_t, uint32_t, uint32_t, uint32_t);
#define  IAP_WordsProgram  ((iap_wordsprogrm_t)(*((uint32_t *)0x10000008)))


uint32_t  get_cusum32(uint32_t *data_ptr, uint32_t len);

uint8_t check_empty(uint32_t *data_ptr, uint32_t len);


//#define  REMAP_DIS   SCU->TBLREMAPEN.EN = 0;
//#define  REMAP_EN    SCU->TBLREMAPEN.EN = 1;

#define  REMAP_DIS        SCU->TBLREMAPEN.EN = 1; SCU->TBLOFF.Word = 0;
#define  REMAP_EN         SCU->TBLREMAPEN.EN = 1; SCU->TBLOFF.Word = 0x1E000;

#define  FAILED  0
#define  SUCCESS 1


#endif
