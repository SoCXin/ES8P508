#include "ES8P508x.h"
#include "macro.h"
#include "typedef.h"


isp_data_t g_isp_data;   //ͨ��������ͨ��״̬���Ĵ���
extern uint32_t  g_boot_timer;
extern uint32_t  g_frame_timer;


/***************************************************************
��������uart_init
��  ��: UART��ʼ��
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void uart_init(UART_TypeDef *uartx)
{
    /* Select UART function */
    uartx->CON.RXMOD = 7; //����8bit-żУ��
    uartx->CON.TXMOD = 7; //����8bit-żУ��
    uartx->CON.TXFS = 0;  //����ֹͣλ1bit
    uartx->CON.BCS = 1;   //������ʱ��ΪPCLK

    uartx->IE.RBIM = 0;  //�ֽ��������ж�
    uartx->IE.TBIM = 0;
    uartx->IE.TBIE = 0;  //��������ж�ʹ��
    uartx->IE.RBIE = 1;  //���ջ��������ж�ʹ��

    uartx->BRR.Word = 129; //������9600

    uartx->CON.RXEN = 1;  //����ʹ��
    uartx->CON.TXEN = 1;  //����ʹ��

}
/***************************************************************
��������uart0_reset
��  ��: UART0��λ
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void uart0_reset(void)
{
    UART0->CON.RRST = 1; //��������λ
    UART0->CON.TRST = 1;  //��������λ
}
/***************************************************************
��������start_tx
��  ��: ����UART����
����ֵ�����͵��ֽ���
���ֵ����
����ֵ����
***************************************************************/
void start_tx(uint8_t len)
{
    UART0->TBW.Byte[0] = g_isp_data.tx_buf[0];
    g_isp_data.tx_cnt = 0;  //���ͼ�������ʼ��
    g_isp_data.tx_len = len; //���ͳ���

    UART0->IE.TBIE = 1;
}
/***************************************************************
��������UART_TC_IRQHandler
��  ��: UART��������ж�
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void UART_TC_IRQHandler(UART_TypeDef *uartx)
{
    if ((uartx->IF.TBIF == 1) && (uartx->IE.TBIE == 1)) //���ͻ��������ж�
    {
        g_isp_data.tx_cnt++;

        if (g_isp_data.tx_cnt > g_isp_data.tx_len)   //������ɣ�������һ������
        {
            UART0->IE.TBIE = 0;
            g_isp_data.triger = 1;//����״̬��������һ��
        }
        else
        {
            uartx->TBW.Byte[0] = g_isp_data.tx_buf[g_isp_data.tx_cnt];
        }
    }
}
/***************************************************************
��������UART_RBR_IRQHandler
��  ��: UART����������Ч�ж�
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void UART_RBR_IRQHandler(UART_TypeDef *uartx)
{
    volatile uint8_t  buf8;
    g_isp_data.syn = 1;   //ͬ�����

    if ((uartx->IF.RBIF == 1) && (uartx->IE.RBIE == 1))
    {
        buf8 = (uint8_t)uartx->RBR.Byte[0];

        if ((buf8 == SYN) && (g_isp_data.step == WAIT_REV_INS))
        {
            g_boot_timer = Boot_OVERTIME_2;
            g_isp_data.tx_buf[0] = ACK;
            g_isp_data.syn = 1;  //ͬ�����
            start_tx(0);
            g_isp_data.result = ACK;
            g_isp_data.step = END_SEND_OVER;
        }
        else
        {
            if ((UART0->IE.FEIE && UART0->IF.FEIF) || (UART0->IE.PEIE && UART0->IF.PEIF)) //�����żУ��������֡�ṹ����
            {
                buf8 = UART0->RBR.Byte[0];
                UART0->IF.FEIF = 1;
                UART0->IF.PEIF = 1;
                return;
            }

            if (g_isp_data.step == WAIT_REV_INS)
            {
                g_isp_data.step = IN_REV_INS;  //���ڽ���ָ����
                g_isp_data.rx_len = 1;
                g_isp_data.rx_cnt = 0;
            }

            g_isp_data.rx_buf[g_isp_data.rx_cnt] = buf8;
            g_isp_data.rx_cnt++;

            if (g_isp_data.rx_cnt > g_isp_data.rx_len)   //������ɣ�������һ������
            {
                g_isp_data.triger = 1;  //����״̬��������һ��
            }
        }
    }
}

/***************************************************************
��������UART0_IRQHandler
��  ��: UART0�жϷ������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void UART0_IRQHandler(void)
{
    g_frame_timer = FRAME_INTERVAL;

    UART_TC_IRQHandler(UART0);  //�������
    UART_RBR_IRQHandler(UART0); //��������
}

