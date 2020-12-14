;*******************************************************************************
; *file       : startup_HR8P506.s
; *description: ES8P508 Device Startup File for IAR8.3
; *author     : Eastsoft MCU Software Team
; *version    : V0.01
; *data       : 8/24/2018
;
; *Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*******************************************************************************


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        EXTERN  STL_StartUp
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     STL_StartUp                   ; Reset Handler

        DCD     NMI_IRQHandler                 ; NMI Handler
        DCD     HardFault_IRQHandler           ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_IRQHandler                 ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_IRQHandler              ; PendSV Handler
        DCD     SysTick_IRQHandler             ; SysTick Handler

        ; External Interrupts
        DCD     PINT0_IRQHandler          ;16, PINT0 IRQHandler
        DCD     PINT1_IRQHandler          ;17, PINT1 IRQHandler
        DCD     PINT2_IRQHandler          ;18, PINT2 IRQHandler
        DCD     PINT3_IRQHandler          ;19, PINT3 IRQHandler
        DCD     PINT4_IRQHandler          ;20, PINT4 IRQHandler
        DCD     PINT5_IRQHandler          ;21, PINT5 IRQHandler
        DCD     PINT6_IRQHandler          ;22, PINT6 IRQHandler
        DCD     PINT7_IRQHandler          ;23, PINT7 IRQHandler
        DCD     T16N0_IRQHandler          ;24, T16N0 IRQHandler
        DCD     T16N1_IRQHandler          ;25, T16N1 IRQHandler
        DCD     T16N2_IRQHandler          ;26, T16N2 IRQHandler
        DCD     T16N3_IRQHandler          ;27, T16N3 IRQHandler
        DCD     T32N0_IRQHandler          ;28, T32N0 IRQHandler
        DCD     0                         ;29, Reserved
        DCD     IWDT_IRQHandler           ;30, IWDT IRQHandler
        DCD     WWDT_IRQHandler           ;31, WWDT IRQHandler
        DCD     CCM_IRQHandler            ;32, WDT IRQHandler
        DCD     PLK_IRQHandler            ;33, PLK IRQHandler
        DCD     LVD_IRQHandler            ;34, LVD IRQHandler
        DCD     KINT_IRQHandler           ;35, KINT IRQHandler
        DCD     RTC_IRQHandler            ;36, RTC IRQHandler
        DCD     ADC_IRQHandler            ;37, ADC IRQHandler
        DCD     0                         ;38, Reserved
        DCD     AES_IRQHandler            ;39, AES IRQHandler
        DCD     UART0_IRQHandler          ;40, UART0 IRQHandler
        DCD     UART1_IRQHandler          ;41, UART1 IRQHandler
        DCD     UART2_IRQHandler          ;42, UART2 IRQHandler
        DCD     UART3_IRQHandler          ;43, UART3 IRQHandler
        DCD     UART4_IRQHandler          ;44, UART4 IRQHandler
        DCD     UART5_IRQHandler          ;45, UART5 IRQHandler
        DCD     SPI0_IRQHandler           ;46, SPI0 IRQHandler
        DCD     I2C0_IRQHandler           ;47, I2C0 IRQHandler


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_IRQHandler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_IRQHandler
        B NMI_IRQHandler

        PUBWEAK HardFault_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_IRQHandler
        B HardFault_IRQHandler

        PUBWEAK SVC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_IRQHandler
        B SVC_IRQHandler

        PUBWEAK PendSV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_IRQHandler
        B PendSV_IRQHandler

        PUBWEAK SysTick_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_IRQHandler
        B SysTick_IRQHandler

        PUBWEAK PINT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT0_IRQHandler
        B PINT0_IRQHandler

        PUBWEAK PINT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT1_IRQHandler
        B PINT1_IRQHandler

        PUBWEAK PINT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT2_IRQHandler
        B PINT2_IRQHandler

        PUBWEAK PINT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT3_IRQHandler
        B PINT3_IRQHandler

        PUBWEAK PINT4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT4_IRQHandler
        B PINT4_IRQHandler

        PUBWEAK PINT5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT5_IRQHandler
        B PINT5_IRQHandler

        PUBWEAK PINT6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT6_IRQHandler
        B PINT6_IRQHandler

        PUBWEAK PINT7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT7_IRQHandler
        B PINT7_IRQHandler

        PUBWEAK T16N0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N0_IRQHandler
        B T16N0_IRQHandler

        PUBWEAK T16N1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N1_IRQHandler
        B T16N1_IRQHandler

        PUBWEAK T16N2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N2_IRQHandler
        B T16N2_IRQHandler

        PUBWEAK T16N3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N3_IRQHandler
        B T16N3_IRQHandler

        PUBWEAK T32N0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T32N0_IRQHandler
        B T32N0_IRQHandler

        PUBWEAK IWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDT_IRQHandler
        B IWDT_IRQHandler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

        PUBWEAK PLK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PLK_IRQHandler
        B PLK_IRQHandler

        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES_IRQHandler
        B AES_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK KINT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
KINT_IRQHandler
        B KINT_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK CCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CCM_IRQHandler
        B CCM_IRQHandler

        END
;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
