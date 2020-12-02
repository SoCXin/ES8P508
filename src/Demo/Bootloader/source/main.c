/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2018/07/04
*��  ��:  Bootloader��ʾ����
          MCU��ES8P5088
          RX��PB0  TX��PB1  BootPin��PB3
          �����ʣ�9600  У��λ��żУ��  ֹͣλ��1λ
          ��ʾ������ο��ĵ� AN082_Ӧ�ñʼ�_ES8Pϵ��MCU bootloader
*��  ע:  ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
��������systick_init
��  ��: Systick��ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void systick_init(void)
{
    SysTick->CTRL = 0x07;
    SysTick->LOAD = 20000;  //ϵͳʱ��20M��1ms����һ���ж�
    SysTick->VAL = 0;
}
/***************************************************************
��������gpio_init
��  ��: GPIO��ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void gpio_init(void)
{
    SCU->PROT.Word = 0X55AA6996;
    SCU->PCLKEN0.GPIO_EN = 1;
    SCU->PCLKEN1.UART0_EN = 1;

    //BootPIN:PB3
    GPIO->PBDIR.DIR_3 = 1; //����ر�
    GPIO->PBINEB.INEB_3 = 0; //�����
    GPIO->PBPDE.PDEN_3 = 1; //��������

    //RX:PB0
    GPIO->PBDIR.DIR_0 = 1; //����ر�
    GPIO->PBINEB.INEB_0 = 0; //�����
    GPIO->PBFUNC0.PB0 = 2;   //FUNC2 RXD

    //TX:PB1
    GPIO->PBDIR.DIR_1 = 0; //�����
    GPIO->PBINEB.INEB_1 = 1; //����ر�
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
            __disable_irq();  //�ٽ�δ��뱣��

            while (g_isp_data.triger == 1)
            {
                uart_proc_fsm();  //isp����״̬������
            }

            __enable_irq();
        }

        if (g_boot == 1) //��Ҫ��������flash
        {
            JumpToApp(APP_ADDR);
        }
    }
}
