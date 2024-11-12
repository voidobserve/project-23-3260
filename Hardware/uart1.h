#ifndef __UART1_H
#define __UART1_H

#include "include.h" // 使用芯片官方提供的头文件
#include "my_config.h"

enum
{
    CUR_RECV_STATUS_NONE = 0, // 无状态，默认状态
    CUR_RECV_STATUS_SEG1,     //
    CUR_RECV_STATUS_SEG2,     //
    CUR_RECV_STATUS_POINT,
    CUR_RECV_STATUS_LED,
    CUR_RECV_STATUS_END, // 结束接收

    CUR_RECV_STATUS_ERR, // 接收协议头和协议尾出错(协议头和协议尾的格式不对)

    CUR_RECV_STATUS_COMPLETE, // 完成接收
};
extern volatile u8 flag_cur_recv_status; // 当前接收的状态(作为状态机)

typedef struct
{
    u8 seg1;  // 存放控制第一位数码管的指令
    u8 seg2;  // 存放控制第二位数码管的指令
    u8 point; // 存放控制数码管小数点显示的指令
    u8 led;   // 存放控制触摸按键对应的LED显示的指令
}instruction_t;
extern volatile instruction_t instruction; // 存放从串口接收的指令，0xFF表示无效指令

extern void uart1_config(void);
extern void uart1_recv_err_handle(void);


#endif