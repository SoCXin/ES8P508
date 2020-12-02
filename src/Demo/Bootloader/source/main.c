/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2018/07/04
*描  述:  Bootloader演示程序
          MCU：ES8P5088
          RX：PB0  TX：PB1  BootPin：PB3
          波特率：9600  校验位：偶校验  停止位：1位
          演示方法请参考文档 AN082_应用笔记_ES8P系列MCU bootloader
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "ES8P508x.h"
#include "macro.h"
#include "typedef.h"
#include "lib_flashiap.h"

extern isp_data_t g_isp_data;
extern uint32_t  g_boot_timer;
extern uint8_t   g_boot;

void uart_init(UART_TypeDef *uartx);
void uart_proc_fsm(void);
void fsm_init(void);
void JumpToApp(uint32_t addr);


/***************************************************************
函数名：systick_init
描  述: Systick初始化
输入值：无
输出值：无
返回值：无
***************************************************************/
void systick_init(void)
{
    SysTick->CTRL = 0x07;
    SysTick->LOAD = 20000;  //系统时钟20M，1ms产生一次中断
    SysTick->VAL = 0;
}
/***************************************************************
函数名：gpio_init
描  述: GPIO初始化
输入值：无
输出值：无
返回值：无
***************************************************************/
void gpio_init(void)
{
    SCU->PROT.Word = 0X55AA6996;
    SCU->PCLKEN0.GPIO_EN = 1;
    SCU->PCLKEN1.UART0_EN = 1;

    //BootPIN:PB3
    GPIO->PBDIR.DIR_3 = 1; //输出关闭
    GPIO->PBINEB.INEB_3 = 0; //输入打开
    GPIO->PBPDE.PDEN_3 = 1; //弱下拉打开

    //RX:PB0
    GPIO->PBDIR.DIR_0 = 1; //输出关闭
    GPIO->PBINEB.INEB_0 = 0; //输入打开
    GPIO->PBFUNC0.PB0 = 2;   //FUNC2 RXD

    //TX:PB1
    GPIO->PBDIR.DIR_1 = 0; //输出打开
    GPIO->PBINEB.INEB_1 = 1; //输入关闭
    GPIO->PBFUNC0.PB1 = 2;   //FUNC2 TXD


}
int SystemInit(void)
{

    return 0;
}

int main()
{
    gpio_init();
    uart_init(UART0);
    fsm_init();
    NVIC_EnableIRQ(UART0_IRQn);
    FlashIAP_RegUnLock();
    FlashIAP_Enable();
    IAP->WPROT0.Word = 0x00000000;
    IAP->WPROT1.Word = 0x00000000;

    systick_init();

    while (1)
    {
        if (g_isp_data.triger == 1)
        {
            __disable_irq();  //临界段代码保护

            while (g_isp_data.triger == 1)
            {
                uart_proc_fsm();  //isp命令状态机处理
            }

            __enable_irq();
        }

        if (g_boot == 1) //需要引导程序到flash
        {
            JumpToApp(APP_ADDR);
        }
    }
}
