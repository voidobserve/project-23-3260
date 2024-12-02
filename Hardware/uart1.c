#include "uart1.h"
#include <string.h>

#define UART1_BAUD (115200UL)
#define USER_UART1_BAUD ((SYSCLK - UART1_BAUD) / (UART1_BAUD))

#define PROTOCOL_HEAD ((u8)0xA5) // 协议头
#define PROTOCOL_TAIL ((u8)0x5A) // 协议尾

volatile u8 flag_cur_recv_status = CUR_RECV_STATUS_NONE; // 当前接收的状态(作为状态机)

// 定义存放指令的结构体变量，0xFF表示无效的指令，会清空显示
volatile instruction_t instruction = {
    0xFF, // seg1
    0xFF, // seg2
    0xFF, // point
    0xFF, // led
};

void uart1_config(void)
{
    P1_MD0 &= ~(GPIO_P12_MODE_SEL(0x3)); // 配置为输入模式
    FIN_S8 |= GPIO_FIN_SEL_P12;          // uart1_rx 输入功能 pin 脚选择

    __EnableIRQ(UART1_IRQn); // 打开UART模块中断
    IE_EA = 1;               // 打开总中断

    UART1_BAUD1 = (USER_UART1_BAUD >> 8) & 0xFF; // 配置波特率高八位
    UART1_BAUD0 = USER_UART1_BAUD & 0xFF;        // 配置波特率低八位
    UART1_CON0 = UART_STOP_BIT(0x0) |            // 8bit数据，1bit停止位，使能中断
                 UART_RX_IRQ_EN(0x1) |
                 UART_EN(0x1);
}

void uart1_recv_err_handle(void)
{
    if (CUR_RECV_STATUS_ERR == flag_cur_recv_status)
    {
// 如果接收协议头和协议尾出错
#if USE_MY_DEBUG
        // printf("recv err\n");
#endif
        memset(&instruction, 0xFF, sizeof(instruction));
        memset(aip650_show_buff, 0x00, ARRAY_SIZE(aip650_show_buff));
        aip650_show_refresh();

        flag_cur_recv_status = CUR_RECV_STATUS_NONE;
    }

    if (tmr0_cnt >= 10)
    {
// 接收到协议头后，超过10ms没有收到数据
#if USE_MY_DEBUG
        // printf("recv time out\n");
#endif
        memset(&instruction, 0xFF, sizeof(instruction));
        memset(aip650_show_buff, 0x00, ARRAY_SIZE(aip650_show_buff));
        aip650_show_refresh();
        flag_cur_recv_status = CUR_RECV_STATUS_NONE;
        tmr0_disable();
        tmr0_cnt = 0;
    }

    // printf("tmr0 cnt %d\n", (u16)tmr0_cnt);
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
        tmr0_cnt = 0; // 每次接收到数据，清空超时计数
        tmr0_enable();

        if (flag_cur_recv_status == CUR_RECV_STATUS_NONE &&
            uart_data == PROTOCOL_HEAD)
        {
            // 协议头
            flag_cur_recv_status = CUR_RECV_STATUS_SEG1;
            // tmr0_cnt = 0;
            // tmr0_enable();
        }
        else if (flag_cur_recv_status == CUR_RECV_STATUS_SEG1)
        {
            // 接收控制数码管1的数据
            instruction.seg1 = uart_data;
            flag_cur_recv_status = CUR_RECV_STATUS_SEG2;
        }
        else if (flag_cur_recv_status == CUR_RECV_STATUS_SEG2)
        {
            // 接收控制数码管2的数据
            instruction.seg2 = uart_data;
            flag_cur_recv_status = CUR_RECV_STATUS_POINT;
        }
        else if (flag_cur_recv_status == CUR_RECV_STATUS_POINT)
        {
            // 接收控制小数点显示的数据
            instruction.point = uart_data;
            flag_cur_recv_status = CUR_RECV_STATUS_LED;
        }
        else if (flag_cur_recv_status == CUR_RECV_STATUS_LED)
        {
            // 接收控制触摸按键对应的LED的数据
            instruction.led = uart_data;
            flag_cur_recv_status = CUR_RECV_STATUS_END;
        }
        else if (flag_cur_recv_status == CUR_RECV_STATUS_END &&
                 uart_data == PROTOCOL_TAIL)
        {
            // 协议尾
            flag_cur_recv_status = CUR_RECV_STATUS_COMPLETE; // 表示完成接收
            tmr0_disable();
            tmr0_cnt = 0;
        }
        else
        {
            // 如果接收错误(这里只能检测到第一个字节和最后一个字节的数据错误)
            // 切换到对应的状态，由uart1_recv_err_handle()函数处理
            flag_cur_recv_status = CUR_RECV_STATUS_ERR;

            tmr0_disable();
            tmr0_cnt = 0;

#if USE_MY_DEBUG
            // printf("recv err\n");
#endif
        }
    }

    // 退出中断设置IP，不可删除
    __IRQnIPnPop(UART1_IRQn);
}