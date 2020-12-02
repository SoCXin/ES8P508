        .syntax unified
        .cpu cortex-m0
        .arch armv6-m
        .fpu softvfp
        .thumb
 
/*  Stack Configuration
    Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
*/
       
        .equ Stack_Size,  0x00000400
 
        .section  .stack, "wa"
        .align 3
        .global Stack_Mem
        .global Stack_Size
Stack_Mem:     
        .if Stack_Size
        .space   Stack_Size
        .endif
        .size    Stack_Mem,.-Stack_Mem
        .set     Stack_Size,.-Stack_Mem
__initial_sp:
 
 
/*
 <h> Heap Configuration
   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
</h>
*/
 
        .equ     Heap_Size,       0x00000010
 
        .section  .heap, "wa"
        .align 3
 
        .global Heap_Mem_Start
        .global Heap_Mem_End
Heap_Mem_Start:     
        .if Heap_Size
        .space   Heap_Size
        .endif        
Heap_Mem_End:     
 
 
/* Vector Table Mapped to Address 0 at Reset*/
                                        
        .section  .vectors, "wax"
        .global  __vector
        .type  __vector, %object
        
__vector: 
                .long     __initial_sp  /* Top of Stack*/
                .long     Reset_IRQHandler  /*Reset_IRQHandler*/    
                .long     NMI_IRQHandler  /* NMI IRQIRQHandler*/
                .long     HardFault_IRQHandler         /* Hard Fault IRQIRQHandler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     SVC_IRQHandler               /* SVCall IRQIRQHandler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     PendSV_IRQHandler            /* PendSV IRQIRQHandler*/
                .long     SysTick_IRQHandler           /* SysTick IRQIRQHandler*/
 
                /* External Interrupts*/
                .long     PINT0_IRQHandler /*16, PINT0 IRQHandler   */
                .long     PINT1_IRQHandler /*17, PINT1 IRQHandler   */
                .long     PINT2_IRQHandler /*18, PINT2 IRQHandler   */
                .long     PINT3_IRQHandler /*19, PINT3 IRQHandler   */
                .long     PINT4_IRQHandler /*20, PINT4 IRQHandler   */
                .long     PINT5_IRQHandler /*21, PINT5 IRQHandler   */
                .long     PINT6_IRQHandler /*22, PINT6 IRQHandler   */
                .long     PINT7_IRQHandler /*23, PINT7 IRQHandler   */
                .long     T16N0_IRQHandler /*24, T16N0 IRQHandler   */
                .long     T16N1_IRQHandler /*25, T16N1 IRQHandler   */
                .long     T16N2_IRQHandler /*26, T16N2 IRQHandler   */
                .long     T16N3_IRQHandler /*27, T16N3 IRQHandler   */
                .long     T32N0_IRQHandler /*28, T32N0 IRQHandler   */
                .long     0                /*29, Reserved           */
                .long     IWDT_IRQHandler  /*30, IWDT IRQHandler    */
                .long     WWDT_IRQHandler  /*31, WWDT IRQHandler    */
                .long     CCM_IRQHandler   /*32, WDT IRQHandler     */
                .long     PLK_IRQHandler   /*33, PLK IRQHandler     */
                .long     LVD_IRQHandler   /*34, LVD IRQHandler     */
                .long     KINT_IRQHandler  /*35, KINT IRQHandler    */
                .long     RTC_IRQHandler   /*36, RTC IRQHandler     */
                .long     ADC_IRQHandler   /*37, ADC IRQHandler     */
                .long     0                /*38, Reserved           */
                .long     AES_IRQHandler   /*39, AES IRQHandler     */
                .long     UART0_IRQHandler /*40, UART0 IRQHandler   */
                .long     UART1_IRQHandler /*41, UART1 IRQHandler   */
                .long     UART2_IRQHandler /*42, UART2 IRQHandler   */
                .long     UART3_IRQHandler /*43, UART3 IRQHandler   */
                .long     UART4_IRQHandler /*44, UART4 IRQHandler   */
                .long     UART5_IRQHandler /*45  UART5 IRQHandler   */
                .long     SPI0_IRQHandler  /*46, SPI0 IRQHandler    */
                .long     I2C0_IRQHandler  /*47, I2C0 IRQHandler    */
 
               .size  __vector, .-__vector
                
.thumb
                .text
                .thumb_func
                .global  Reset_IRQHandler
                .type Reset_IRQHandler,%function
Reset_IRQHandler:
           
                .extern main
                .extern InitRam

                LDR     R0, =InitRam
                BLX     R0
                LDR     R0, =main
                BLX     R0
             
               .size  Reset_IRQHandler, .-Reset_IRQHandler
 
                .text
/* Dummy Exception IRQHandlers (infinite loops which can be modified)*/                
               
                 .weak NMI_IRQHandler
                 .type NMI_IRQHandler,%function
NMI_IRQHandler:     
                 B       .
                 .size  NMI_IRQHandler, .-NMI_IRQHandler
                
                 .weak  HardFault_IRQHandler
                 .type  HardFault_IRQHandler,%function
HardFault_IRQHandler:
                B .
                .size  HardFault_IRQHandler, .-HardFault_IRQHandler
                
                .weak SVC_IRQHandler
                .type SVC_IRQHandler,%function
SVC_IRQHandler: 
                B       .
                .size  SVC_IRQHandler, .-SVC_IRQHandler
              
                
                .weak  PendSV_IRQHandler
                .type  PendSV_IRQHandler,%function
PendSV_IRQHandler:
                B .
          .size  PendSV_IRQHandler, .-PendSV_IRQHandler
                 
                .weak  SysTick_IRQHandler
                .type  SysTick_IRQHandler,%function
SysTick_IRQHandler: 
                B .
                .size  SysTick_IRQHandler, .-SysTick_IRQHandler
 
                .global Default_IRQHandler
                .type  Default_IRQHandler,%function
Default_IRQHandler: 
                B       .
                .size  Default_IRQHandler, .-Default_IRQHandler
                .macro IRQ handler
                .weak \handler
                .set \handler,Default_IRQHandler 
                .endm
                
				IRQ PINT0_IRQHandler   
				IRQ PINT1_IRQHandler   
				IRQ PINT2_IRQHandler   
				IRQ PINT3_IRQHandler   
				IRQ PINT4_IRQHandler   
				IRQ PINT5_IRQHandler   
				IRQ PINT6_IRQHandler   
				IRQ PINT7_IRQHandler   
				IRQ T16N0_IRQHandler   
				IRQ T16N1_IRQHandler   
				IRQ T16N2_IRQHandler   
				IRQ T16N3_IRQHandler   
				IRQ T32N0_IRQHandler   
				IRQ IWDT_IRQHandler   
				IRQ WWDT_IRQHandler    
				IRQ CCM_IRQHandler     
				IRQ PLK_IRQHandler     
				IRQ LVD_IRQHandler    
				IRQ KINT_IRQHandler     
				IRQ RTC_IRQHandler    
				IRQ ADC_IRQHandler    
				IRQ AES_IRQHandler       
				IRQ UART0_IRQHandler  
				IRQ UART1_IRQHandler  
				IRQ UART2_IRQHandler   
				IRQ UART3_IRQHandler  
				IRQ UART4_IRQHandler   
				IRQ UART5_IRQHandler   
				IRQ SPI0_IRQHandler   
				IRQ I2C0_IRQHandler   

				.end
