#include "ES8P508x.h"
#include "macro.h"
#include "typedef.h"


isp_data_t g_isp_data;   //通信数据与通信状态机寄存器
extern uint32_t  g_boot_timer;
extern uint32_t  g_frame_timer;


/***************************************************************
函数名：uart_init
描  述: UART初始化
输入值：uart基地址
输出值：无
返回值：无
***************************************************************/
void uart_init(UART_TypeDef *uartx)
{
    /* Select UART function */
    uartx->CON.RXMOD = 7; //发送8bit-偶校验
    uartx->CON.TXMOD = 7; //接收8bit-偶校验
    uartx->CON.TXFS = 0;  //发送停止位1bit
    uartx->CON.BCS = 1;   //波特率时钟为PCLK

    uartx->IE.RBIM = 0;  //字节满产生中断
    uartx->IE.TBIM = 0;
    uartx->IE.TBIE = 0;  //发送完成中断使能
    uartx->IE.RBIE = 1;  //接收缓冲器满中断使能

    uartx->BRR.Word = 129; //波特率9600

    uartx->CON.RXEN = 1;  //接收使能
    uartx->CON.TXEN = 1;  //发送使能

}
/***************************************************************
函数名：uart0_reset
描  述: UART0复位
输入值：无
输出值：无
返回值：无
***************************************************************/
void uart0_reset(void)
{
    UART0->CON.RRST = 1; //接收器复位
    UART0->CON.TRST = 1;  //发送器复位
}
/***************************************************************
函数名：start_tx
描  述: 启动UART发送
输入值：发送的字节数
输出值：无
返回值：无
***************************************************************/
void start_tx(uint8_t len)
{
    UART0->TBW.Byte[0] = g_isp_data.tx_buf[0];
    g_isp_data.tx_cnt = 0;  //发送计数器初始化
    g_isp_data.tx_len = len; //发送长度

    UART0->IE.TBIE = 1;
}
/***************************************************************
函数名：UART_TC_IRQHandler
描  述: UART发送完成中断
输入值：uart基地址
输出值：无
返回值：无
***************************************************************/
void UART_TC_IRQHandler(UART_TypeDef *uartx)
{
    if ((uartx->IF.TBIF == 1) && (uartx->IE.TBIE == 1)) //发送缓冲器空中断
    {
        g_isp_data.tx_cnt++;

        if (g_isp_data.tx_cnt > g_isp_data.tx_len)   //发送完成，触发下一步工作
        {
            UART0->IE.TBIE = 0;
            g_isp_data.triger = 1;//触发状态机进入下一步
        }
        else
        {
            uartx->TBW.Byte[0] = g_isp_data.tx_buf[g_isp_data.tx_cnt];
        }
    }
}
/***************************************************************
函数名：UART_RBR_IRQHandler
描  述: UART接收数据有效中断
输入值：uart基地址
输出值：无
返回值：无
***************************************************************/
void UART_RBR_IRQHandler(UART_TypeDef *uartx)
{
    volatile uint8_t  buf8;
    g_isp_data.syn = 1;   //同步完成

    if ((uartx->IF.RBIF == 1) && (uartx->IE.RBIE == 1))
    {
        buf8 = (uint8_t)uartx->RBR.Byte[0];

        if ((buf8 == SYN) && (g_isp_data.step == WAIT_REV_INS))
        {
            g_boot_timer = Boot_OVERTIME_2;
            g_isp_data.tx_buf[0] = ACK;
            g_isp_data.syn = 1;  //同步完成
            start_tx(0);
            g_isp_data.result = ACK;
            g_isp_data.step = END_SEND_OVER;
        }
        else
        {
            if ((UART0->IE.FEIE && UART0->IF.FEIF) || (UART0->IE.PEIE && UART0->IF.PEIF)) //如果奇偶校验错误或者帧结构错误
            {
                buf8 = UART0->RBR.Byte[0];
                UART0->IF.FEIF = 1;
                UART0->IF.PEIF = 1;
                return;
            }

            if (g_isp_data.step == WAIT_REV_INS)
            {
                g_isp_data.step = IN_REV_INS;  //正在接收指令码
                g_isp_data.rx_len = 1;
                g_isp_data.rx_cnt = 0;
            }

            g_isp_data.rx_buf[g_isp_data.rx_cnt] = buf8;
            g_isp_data.rx_cnt++;

            if (g_isp_data.rx_cnt > g_isp_data.rx_len)   //接收完成，触发下一步工作
            {
                g_isp_data.triger = 1;  //触发状态机进入下一步
            }
        }
    }
}

/***************************************************************
函数名：UART0_IRQHandler
描  述: UART0中断服务程序
输入值：无
输出值：无
返回值：无
***************************************************************/
void UART0_IRQHandler(void)
{
    g_frame_timer = FRAME_INTERVAL;

    UART_TC_IRQHandler(UART0);  //发送完成
    UART_RBR_IRQHandler(UART0); //接收数据
}

