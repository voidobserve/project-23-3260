#include "uart1.h"

#define UART1_BAUD (115200UL)
#define USER_UART1_BAUD ((SYSCLK - UART1_BAUD) / (UART1_BAUD))

#define PROTOCOL_HEAD ((u8)0xA5) // 协议头
#define PROTOCOL_TAIL ((u8)0x5A) // 协议尾

enum
{
    CUR_RECV_STATUS_NONE = 0,    // 无状态，默认状态
    CUR_RECV_STATUS_BEGIN,   // 开始接收
    CUR_RECV_STATUS_RECVING, // 接收数据中
    CUR_RECV_STATUS_END,     // 结束接收
};
volatile u8 flag_cur_recv_status = CUR_RECV_STATUS_NONE; // 当前接收的状态(作为状态机)

u8 instruction_seg1 = 0;

// u8 uart1_recv_buf[6] = {0};

void uart1_config(void)
{
    P1_MD0 &= ~(GPIO_P11_MODE_SEL(0x3)); // 配置为输入模式
    FIN_S8 |= GPIO_FIN_SEL_P12;          // uart1_rx 输入功能 pin 脚选择

    __EnableIRQ(UART1_IRQn); // 打开UART模块中断
    IE_EA = 1;               // 打开总中断

    UART1_BAUD1 = (USER_UART1_BAUD >> 8) & 0xFF; // 配置波特率高八位
    UART1_BAUD0 = USER_UART1_BAUD & 0xFF;        // 配置波特率低八位
    UART1_CON0 = UART_STOP_BIT(0x0) |            // 8bit数据，1bit停止位，使能中断
                 UART_RX_IRQ_EN(0x1) |
                 UART_EN(0x1);
}

void UART1_IRQHandler(void) interrupt UART1_IRQn
{
    u8 uart_data = 0;

    // 进入中断设置IP，不可删除
    __IRQnIPnPush(UART1_IRQn);

    // ---------------- 用户函数处理 -------------------

    // RX接收完成中断
    if (UART1_STA & UART_RX_DONE(0x1))
    {
        uart_data = UART1_DATA;

        if (flag_cur_recv_status == CUR_RECV_STATUS_NONE && uart_data == 0xA5)
        {

        }
    }

    // 退出中断设置IP，不可删除
    __IRQnIPnPop(UART1_IRQn);
}