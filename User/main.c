/**
 ******************************************************************************
 * @file    main.c
 * @author  HUGE-IC Application Team
 * @version V1.0.0
 * @date    05-11-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2021 HUGE-IC</center></h2>
 *
 * 版权说明后续补上
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "include.h"
#include "my_config.h"

/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
    // 看门狗默认打开, 复位时间2s
    system_init();

    WDT_KEY = WDT_KEY_VAL(0xDD); //  关闭看门狗

    // 关闭HCK和HDA的调试功能:
    WDT_KEY = 0x55;
    IO_MAP &= ~0x01;
    WDT_KEY = 0xBB;

    send_keyval_pin_init();   // 初始化键值的发送引脚
    send_keyval_timer_init(); // 初始化发送键值的引脚所使用到的定时器，定时器默认关闭

    aip650_config();

    /* 按键初始化 */
    tk_param_init();
    tmr0_config(); // 配置检测串口接收数据超时的定时器
#if USE_MY_DEBUG
    uart0_config(); // 调试使用到的串口
#endif
    uart1_config();

    /* 系统主循环 */
    while (1)
    {
        /* 按键扫描函数 */
        __tk_scan(); // 使用了库里面的接口（闭源库）

        /* 用户循环扫描函数接口 */
        user_handle();
        uart1_recv_err_handle();

        if (flag_cur_recv_status == CUR_RECV_STATUS_COMPLETE)
        {
#if USE_MY_DEBUG
            printf("recv complete\n");

            printf("seg1 %#x\n", (u16)instruction.seg1);
            printf("seg2 %#x\n", (u16)instruction.seg2);
            printf("point %#x\n", (u16)instruction.point);
            printf("led %#x\n", (u16)instruction.led);
            // printf("addr  %p\n", &instruction);
#endif
            aip650_show_handle(instruction);

            memset(&instruction, 0xFF, sizeof(instruction)); // 清空存放指令的结构体变量
            flag_cur_recv_status = CUR_RECV_STATUS_NONE;     // 清除接收完成标志
        }

        // /* 喂狗 :建议不要关闭看门狗，默认2s复位*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
