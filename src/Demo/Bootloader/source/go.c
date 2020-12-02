#include "ES8P508x.h"
#include "macro.h"
#include "typedef.h"
#include "lib_flashiap.h"

#define APP_ADDRESS BOOT_TO_ADDR
typedef  void (*FunVoidType)(void);

static uint32_t ApplicationAddress;
static uint32_t m_JumpAddress;
static FunVoidType JumpToApplication;

/***************************************************************
函数名：sfr_reset
描  述: 引导程序前对BootROM里使用的寄存器恢复复位值
输入值：无
输出值：无
返回值：无
***************************************************************/
void sfr_reset(void)
{

    SysTick->CTRL = 0x00;
    SysTick->LOAD = 0;


    SCU->PRSTEN1.UART0_RST = 1; //软件复位UART0
    SCU->PRSTEN0.GPIO_RST = 1;  //软件复位GPIOB


    SCU->PROT.Word = 0;
}

/***************************************************************
函数名：JumpToApp
描  述: 引导程序到指定位置
输入值：目标地址，必须256byte对齐
输出值：无
返回值：无
***************************************************************/
void JumpToApp(uint32_t addr)
{
    __disable_irq(); //关中断
    NVIC->ICER[0] = 0xFFFFFFFF;  //关闭所有IRQ

    ApplicationAddress = addr & 0xFFFFFF00; //保证地址256对齐
//  REMAP_EN;
    REMAP_DIS;
    SCU->TBLOFF.TBLOFF = ApplicationAddress; //中断向量重映射

    m_JumpAddress = *(volatile uint32_t *)(ApplicationAddress + 4);  //获取复位向量
    JumpToApplication = (FunVoidType) m_JumpAddress;

    sfr_reset();  //恢复寄存器
    __enable_irq();  //使能中断

    __set_MSP(*(volatile uint32_t *) ApplicationAddress);  //初始化栈顶
    JumpToApplication();  //程序跳转到复位向量指向的位置
}
