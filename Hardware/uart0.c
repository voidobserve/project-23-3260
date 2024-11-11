#include "uart0.h"

#define UART0_BAUD (115200UL)

// 重写putchar()函数
char putchar(char uart_data)
{
    UART0_DATA = uart_data;
    while (!(UART0_STA & UART_TX_DONE(0x1)))
        ; // 等待发送完成

    return uart_data;
}

void uart0_config(void)
{
    P0_MD0 &= ~GPIO_P02_MODE_SEL(0x03);
    P0_MD0 |= GPIO_P02_MODE_SEL(0x01); // 输出模式
    FOUT_S02 = GPIO_FOUT_UART0_TX; // 复用为uart0_tx

    UART0_BAUD1 = (((SYSCLK - UART0_BAUD) / UART0_BAUD) >> 8) & 0xFF;
    UART0_BAUD0 = ((SYSCLK - UART0_BAUD) / UART0_BAUD) & 0xFF;
    UART0_CON0 = UART_EN(0x01); // UART使能
}