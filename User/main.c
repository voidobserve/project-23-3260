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

    // tmr1_enable(); // 打开发送键值的引脚所使用到的定时器，测试用，看看定时器中断是否按配置的时间触发

    // tmr3_config(); // 配置定时器，每10ms产生一次中断，对应的计数值+1，用来判断按键的短按、长按和持续

    aip650_config();

    /* 按键初始化 */
    tk_param_init();

    uart0_config(); // 调试使用到的串口

    /* 系统主循环 */
    while (1)
    {
        /* 按键扫描函数 */
        __tk_scan(); // 使用了库里面的接口（闭源库）

        /* 用户循环扫描函数接口 */
        user_handle();

        // aip650_show_data(14, 15);
        // aip650_show_refresh();
        // delay_ms(500);

        // aip650_show_buff[1] = 0x80;

        // aip650_show_led_of_touch(0x1F);
        // aip650_show_refresh();
        // delay_ms(500);

        // /* 喂狗 :建议不要关闭看门狗，默认2s复位*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
