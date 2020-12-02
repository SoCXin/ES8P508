
#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "ES8P508x.h"

extern uint32_t SysCount;
extern uint8_t g_wdt_inte_flag;

/************�жϺ�������***********/
void    NMI_IRQHandler(void);
void    HardFault_IRQHandler(void);
void    SVC_IRQHandler(void);
void    PendSV_IRQHandler(void);
void    SysTick_IRQHandler(void);


#endif

