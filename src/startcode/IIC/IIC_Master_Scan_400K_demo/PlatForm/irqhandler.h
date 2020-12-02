
#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "ES8P508x.h"

extern uint32_t SysCount;

extern uint8_t g_2ms_flag;        //2ms标志
extern uint8_t g_10ms_flag;        //10ms标志
extern uint16_t g_10ms_cnt;        //10ms计数

/************中断函数声明***********/
void    NMI_IRQHandler(void);
void    HardFault_IRQHandler(void);
void    SVC_IRQHandler(void);
void    PendSV_IRQHandler(void);
void    SysTick_IRQHandler(void);


#endif

