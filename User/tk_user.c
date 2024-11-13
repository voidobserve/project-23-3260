/**
 ******************************************************************************
 * @file    User/tk_user.c
 * @author  HUGE-IC Application Team
 * @version V1.0.0
 * @date    05-20-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2022 TAIXIN-IC</center></h2>
 *
 *
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

/**
 * @brief  Touchkey  debug uart init function
 * @param  None
 * @retval None
 */
// // xdata u16 led_data[1];                           // LED显示buff
// #define LED_DIS_FREQ (1000000 / 16 / 8 / 60 - 1) // 一个CON的显示时间60Hz    60-1=1M/(LED_COMCON*16*LED_TIME_CON)

// unsigned int xdata display_data = 0;

/**
 * @brief  调试接口IO初始化函数.
 * @param  None
 * @retval None
 */
#if TK_DEBUG_EN
void debug_gpio_config(void)
{
#if 1
    P2_MD0 &= ~GPIO_P21_MODE_SEL(0x03);
    P2_MD0 |= GPIO_P21_MODE_SEL(0x01);
    FOUT_S21 = GPIO_FOUT_UART1_TX;
#else
    P2_MD1 &= ~GPIO_P27_MODE_SEL(0x03);
    P2_MD1 |= GPIO_P27_MODE_SEL(0x01);
    FOUT_S27 = GPIO_FOUT_UART1_TX;
#endif
}
#endif

#if 0
/**
 * @brief  用户代码循环执行函数接口.（触摸按键扫描函数接口）
 * @param  None
 * @retval None
 */
#define DETECT_DOUBLE_CLICK_INTERVAL (100) // 发送间隔
void user_handle(void)
{
    volatile unsigned long int touch_key = __tk_key_flag; // __tk_key_flag单次按键标志

    static volatile unsigned long int KeyOld = 0; // 用于存放长按时，对应的按键

    // 是否长按的标志，0--否，1--是
    // 需要保存长按的状态，表示定时器一直在发送键值
    static unsigned char flag_is_long_press = 0; // 上一次扫描到的按键是否为长按的标志

    static volatile u32 cnt = 0; // 长按计数值

    u32 i = 0; // 循环计数值

    u16 send_data = 0; // 要发送的带有键值的数据

    if (touch_key && 0 == flag_is_long_press && cnt < TK_LONG_KEY_TIME) // 如果有按键按下（并且之前扫描到的不是长按）
    {
        // 通过循环判断是否为长按
        for (i = 0; i < 500000; i++) // 实际上用不到这么大的数字，到了设定的长按时间就会退出
        {
            // 按键扫描函数，使用了库里面的接口（闭源库）
            // 这个函数会更新__tk_key_flag的值
            delay_ms(10);
            __tk_scan();

            if (touch_key == __tk_key_flag)
            {
                // 如果按键键值一致，说明按键一直被按下，未松开
                cnt++;
            }
            else
            {
                // 如果按键键值不一致或是松开了按键
                // cnt = 0;
                break;
            }
            
            if (cnt > TK_LONG_KEY_TIME) // 如果长按超过了这里设置的时间
            {
                flag_is_long_press = 1; // 标记为长按
                break;
            }
        }

        if (cnt > TK_LONG_KEY_TIME)
        {
            flag_is_long_press = 1; // 标记为长按
        }
        else
        {
            // 如果是短按
            cnt = 0; // 清除长按的计数值

            // 判断当前触摸的键值，做对应的操作
            if (TK_CH24_VALIB == touch_key)
            {
                // 如果KEY1被触摸
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH24_VALIB == touch_key)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
                        }
#if USE_MY_DEBUG
                        printf("k1 double press\n");
#endif
                        send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY1);
                        return;
                    }
                }

// 如果不是同一个按键按下或是没有值，说明是短按
#if USE_MY_DEBUG
                printf("k1 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY1); // 发送带有状态的键值
            }
            else if (TK_CH25_VALIB == touch_key)
            {
                // 如果KEY2被触摸
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH25_VALIB == touch_key)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
                        }
#if USE_MY_DEBUG
                        printf("k2 double press\n");
#endif
                        send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY2);
                        return;
                    }
                }

// 如果不是同一个按键按下或是没有值，说明是短按
#if USE_MY_DEBUG
                printf("k2 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY2); // 发送带有状态的键值
            }
            else if (TK_CH23_VALIB == touch_key)
            {
                // 如果KEY3被触摸
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH23_VALIB == touch_key)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
                        }

#if USE_MY_DEBUG
                        printf("k3 double press\n");
#endif
                        send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY3);
                        return;
                    }
                }

                // 如果不是同一个按键按下或是没有值，说明是短按
#if USE_MY_DEBUG
                printf("k3 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY3); // 发送带有状态的键值
            }
            else if (TK_CH17_VALIB == touch_key)
            {
                // 如果KEY4被触摸
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH17_VALIB == touch_key)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
                        }

#if USE_MY_DEBUG
                        printf("k4 double press\n");
#endif
                        send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY4);
                        return;
                    }
                }

                // 如果不是同一个按键按下或是没有值，说明是短按
#if USE_MY_DEBUG
                printf("k4 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY4); // 发送带有状态的键值
            }
            else if (TK_CH15_VALIB == touch_key)
            {
                // 如果KEY5被触摸
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH15_VALIB == touch_key)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
                        }
#if USE_MY_DEBUG
                        printf("k5 double press\n");
#endif
                        send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY5);
                        return;
                    }
                }

// 如果不是同一个按键按下或是没有值，说明是短按
#if USE_MY_DEBUG
                printf("k5 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY5); // 发送带有状态的键值
            }
        }
    }

    if (1 == flag_is_long_press && 0 != touch_key)
    {
        KeyOld = touch_key;

        // 如果之前是长按，现在还未松开
        // 判断当前触摸的键值，做对应的操作
        if (TK_CH24_VALIB == touch_key)
        {
            // 如果KEY1被触摸
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k1 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY1);
            }

            // 若还不松开手，则每隔150ms发送一次带有持续状态信息的键值信号
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

                if (cnt >= 87) // 原本是填90的，但是软件延时有误差，这里只能慢慢调试
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k1 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY1);
                }
            }
        }
        else if (TK_CH25_VALIB == touch_key)
        {
            // 如果KEY2被触摸
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k2 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY2);
            }

            // 若还不松开手，则每隔150ms发送一次带有持续状态信息的键值信号
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

                if (cnt >= 87) // 原本是填90的，但是软件延时有误差，这里只能慢慢调试
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k2 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY2);
                }
            }

            // display_data ^= 0x0200; // 对应的LED状态取反，后面会调用led_display()刷新
            // led_display();          // LED状态更新显示
        }
        else if (TK_CH23_VALIB == touch_key)
        {
            // 如果KEY3被触摸
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k3 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY3);
            }

            // 若还不松开手，则每隔150ms发送一次带有持续状态信息的键值信号
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

                if (cnt >= 87) // 原本是填90的，但是软件延时有误差，这里只能慢慢调试
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k3 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY3);
                }
            }
        }
        else if (TK_CH17_VALIB == touch_key)
        {
            // 如果KEY4被触摸
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // 对应的LED状态取反，后面会调用led_display()刷新
                // led_display();          // LED状态更新显示
#if USE_MY_DEBUG
                printf("k4 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY4);
            }

            // 若还不松开手，则每隔150ms发送一次带有持续状态信息的键值信号
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

                if (cnt >= 87) // 原本是填90的，但是软件延时有误差，这里只能慢慢调试
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k4 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY4);
                }
            }

            // display_data ^= 0x0800; // 对应的LED状态取反，后面会调用led_display()刷新
            // led_display();          // LED状态更新显示
        }
        else if (TK_CH15_VALIB == touch_key)
        {
            // 如果KEY5被触摸
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // 对应的LED状态取反，后面会调用led_display()刷新
                // led_display();          // LED状态更新显示
#if USE_MY_DEBUG
                printf("k5 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY5);
            }

            // 若还不松开手，则每隔150ms发送一次带有持续状态信息的键值信号
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

                if (cnt >= 87) // 原本是填90的，但是软件延时有误差，这里只能慢慢调试
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k5 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY5);
                }
            }

            // display_data ^= 0x0800; // 对应的LED状态取反，后面会调用led_display()刷新
            // led_display();          // LED状态更新显示
        }
    }
    else if (1 == flag_is_long_press && 0 == touch_key)
    {
        // 如果之前是长按，现在却松开了按键
        switch (KeyOld)
        {
        case TK_CH24_VALIB:
#if USE_MY_DEBUG
            printf("k1 long press loose\n");
#endif
            send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY1);
            break;

        case TK_CH25_VALIB:
#if USE_MY_DEBUG
            printf("k2 long press loose\n");
#endif
            send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY2);
            break;

        case TK_CH23_VALIB:
#if USE_MY_DEBUG
            printf("k3 long press loose\n");
#endif
            send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY3);
            break;

        case TK_CH17_VALIB:
#if USE_MY_DEBUG
            printf("k4 long press loose\n");
#endif
            send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY4);
            break;

        case TK_CH15_VALIB:
#if USE_MY_DEBUG
            printf("k5 long press loose\n");
#endif
            send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY5);
            break;
        }

        flag_is_long_press = 0; // 清除标志位
        cnt = 0;
        KeyOld = 0;
    }

#if 0
    if (1 == __tk_long_key_flag) // 如果长按按键（这个功能测试发现不行，不能用）
    {
        __tk_long_key_flag = 0;

        // 这里可以自己处理，添加自己需要的功能

        P11 = 0;
    }
#endif
}
#endif

/**
 * @brief __is_double_click() 判断是否有双击同一个触摸按键,内部最长延时时间：DETECT_DOUBLE_CLICK_INTERVAL
 *
 * @param touch_key_id_const
 * @return u8 0--没有双击同一个触摸按键，1--双击了同一个触摸按键
 */
u8 __is_double_click(const u32 touch_key_id_const)
{
    u8 i = 0;                   // 循环计数值
    volatile u32 touch_key = 0; // 存放每次检测到的按键

    for (; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
    {
        delay_ms(1);
        __tk_scan();
        touch_key = __tk_key_flag;

        if (touch_key_id_const == touch_key)
        {
            // 如果检测到是同一个按键按下，说明是双击
            return 1; // 双击了同一个触摸按键，返回1
        }
    }

    return 0; // 没有双击同一个触摸按键，返回0
}

enum
{
    TOUCH_KEY_SCAN_STATUS_NONE,                  // 空状态，检测是否有按键按下
    TOUCH_KEY_SCAN_STATUS_IS_DETECT_LOOG_PRESS,  // 正在检测是否为长按（要跟检测长按作区分）
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS,  // 正在处理长按
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS,  // 正在处理长按持续（不松手）
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS, // 正在处理短按

    TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE, // 正在等待短按松开
    TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE,  // 正在等待长按松开
    TOUCH_KEY_SCAN_STATUS_IS_END,                      // 收尾处理
};

static volatile u8 touch_key_scan_status = 0; // 非阻塞的按键扫描函数中，使用的状态机

// 非阻塞的按键扫描函数
void touch_key_scan(void)
{
    volatile u32 touch_key = 0;             // __tk_key_flag 单次按键标志
    static u32 touch_key_last = 0;          // 用于存放长按时，对应的按键
    static volatile u32 touch_time_cnt = 0; // 长按计数值

    /* 按键扫描函数 */
    __tk_scan();               // 使用了库里面的接口（闭源库）
    touch_key = __tk_key_flag; // __tk_key_flag 单次按键标志

    if (TOUCH_KEY_SCAN_STATUS_NONE == touch_key_scan_status) // 未检测到按键时
    {
        // 如果有按键按下（并且之前扫描到的不是长按）
        // if (touch_key && touch_time_cnt < LONG_PRESS_TIME_THRESHOLD_MS)
        // if (touch_key)
        // if (touch_key_last != touch_key && touch_key != 0)
        {
            // 判断是否为长按：

            if (touch_key_last == 0) // 如果之前未检测到按键
            {
                touch_key_last = touch_key;
            }
            else if (touch_key_last == touch_key)
            {
                // 如果上次检测到的按键与此次的按键相等，说明按键还未松开
                touch_time_cnt += (1 + ONE_CYCLE_TIME_MS);

                if (touch_time_cnt >= LONG_PRESS_TIME_THRESHOLD_MS)
                {
                    // 如果长按超过了设置的长按时间
                    // 跳转到长按处理
                    touch_time_cnt = 0; // 清除长按时间计数

                    printf("long press\n");
                    touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS;
                }
            }
            else
            {
                // 如果上次检测到的按键与此次的按键不相等，并且上次检测到的按键不等于0
                // touch_time_cnt = 0; // 清除长按时间计数（可以留到收尾处理）

                // 跳转到短按处理
                touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS;

                // printf("short press\n");
            }

            delay_ms(1); //
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS == touch_key_scan_status)
    {
        // 如果是正在处理短按
        bit flag_is_double_click = 0; // 标志位，是否有按键双击

        if (TOUCH_KEY_ID_1 == touch_key_last)
        {
            // 如果KEY1被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
#if USE_MY_DEBUG
                printf("k1 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY1); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
#if USE_MY_DEBUG
                printf("k1 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY1); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
        else if (TOUCH_KEY_ID_2 == touch_key_last)
        {
            // 如果KEY2被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
#if USE_MY_DEBUG
                printf("k2 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY2); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
#if USE_MY_DEBUG
                printf("k2 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY2); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
        else if (TOUCH_KEY_ID_3 == touch_key_last)
        {
            // 如果KEY3被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
#if USE_MY_DEBUG
                printf("k3 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY3); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
#if USE_MY_DEBUG
                printf("k3 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY3); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
        else if (TOUCH_KEY_ID_4 == touch_key_last)
        {
            // 如果KEY4被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
#if USE_MY_DEBUG
                printf("k4 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY4); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
#if USE_MY_DEBUG
                printf("k4 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY4); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
        else if (TOUCH_KEY_ID_5 == touch_key_last)
        {
            // 如果KEY5被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
#if USE_MY_DEBUG
                printf("k5 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY5); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
#if USE_MY_DEBUG
                printf("k5 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY5); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS == touch_key_scan_status)
    {
        // 处理长按
        if (TOUCH_KEY_ID_1 == touch_key)
        {
            // 如果KEY1被触摸

#if USE_MY_DEBUG
            printf("k1 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY1);
        }
        else if (TOUCH_KEY_ID_2 == touch_key)
        {
            // 如果KEY2被触摸

#if USE_MY_DEBUG
            printf("k2 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY2);
        }
        else if (TOUCH_KEY_ID_3 == touch_key)
        {
            // 如果KEY3被触摸

#if USE_MY_DEBUG
            printf("k3 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY3);
        }
        else if (TOUCH_KEY_ID_4 == touch_key)
        {
            // 如果KEY4被触摸

#if USE_MY_DEBUG
            printf("k4 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY4);
        }
        else if (TOUCH_KEY_ID_5 == touch_key)
        {
            // 如果KEY5被触摸

#if USE_MY_DEBUG
            printf("k5 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY5);
        }

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS; // 跳转到长按持续
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS == touch_key_scan_status)
    {
        // 处理长按持续

        if (touch_key_last == touch_key)
        {
            touch_time_cnt++;
            if (TOUCH_KEY_ID_1 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k1 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY1);
                }
            }
            else if (TOUCH_KEY_ID_2 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k2 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY2);
                }
            }
            else if (TOUCH_KEY_ID_3 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k3 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY3);
                }
            }
            else if (TOUCH_KEY_ID_4 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k4 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY4);
                }
            }
            else if (TOUCH_KEY_ID_5 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k5 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY5);
                }
            }

            delay_ms(1);
        }
        else
        {
            // 如果之前检测到的按键与当前检测到的按键不一致，
            // 说明 可能松开了手 或是 一只手按住了原来的按键另一只手按了其他按键

            // 跳转到等待长按松开
            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE;
        }
    }

    if ((TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status) ||
        (TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE == touch_key_scan_status))
    {
        // 如果是等待按键松开
        static volatile u16 loose_cnt = 0; // 存放松手计数值

        if (touch_key == 0)
        {
            loose_cnt++;
            delay_ms(1);
        }
        else
        {
            // 只要有一次检测到按键，说明没有松开手
            loose_cnt = 0;
        }

        if (loose_cnt >= LOOSE_PRESS_CNT_MS) // 这里的比较值需要注意，不能大于变量类型对应的最大值
        {
            loose_cnt = 0; // 清空松手计数
            // 如果 xx ms内没有检测到按键按下，说明已经松开手

            if (TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status)
            {
                if (TOUCH_KEY_ID_1 == touch_key_last)
                {
#if USE_MY_DEBUG
                    printf("k1 long press loose\n");
#endif
                    send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY1);
                }
            }


            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_END; // 跳转到收尾处理
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_END == touch_key_scan_status)
    {
        // 收尾处理
        touch_key = 0;
        touch_key_last = 0;
        touch_time_cnt = 0;

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_NONE;
    }
}

/*************************** (C) COPYRIGHT 2022 TAIXIN-IC ***** END OF FILE *****/
