
#ifndef __IRQHANDLER_H__
#define __IRQHANDLER_H__

#include "lib_config.h"
#include "ES8P508x.h"
#include "type.h"
#include "systick.h"

extern uint32_t SysCount;

/************ÖÐ¶Ïº¯ÊýÉùÃ÷***********/
void    NMI_IRQHandler(void);
void    HardFault_IRQHandler(void);
void    SVC_IRQHandler(void);
void    PendSV_IRQHandler(void);
void    SysTick_IRQHandler(void);


#endif

