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
// xdata u16 led_data[1];                           // LED显示buff
#define LED_DIS_FREQ (1000000 / 16 / 8 / 60 - 1) // 一个CON的显示时间60Hz    60-1=1M/(LED_COMCON*16*LED_TIME_CON)

unsigned int xdata display_data = 0;

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

/**
 * @brief  用户代码循环执行函数接口.（触摸按键扫描函数接口）
 * @param  None
 * @retval None
 */
#define send_sp (100)
void user_handle(void)
{
    volatile unsigned long int KeyOnOutput = __tk_key_flag; // __tk_key_flag单次按键标志

    static volatile unsigned long int KeyOld = 0; // 用于存放长按时，对应的按键

    // 是否长按的标志，0--否，1--是
    // 需要保存长按的状态，表示定时器一直在发送键值
    static unsigned char long_touch_flag = 0; // 上一次扫描到的按键是否为长按的标志

    static volatile u32 cnt = 0; // 长按计数值

    u32 i = 0; // 循环计数值

    u16 send_data = 0; // 要发送的带有键值的数据

    if (KeyOnOutput && 0 == long_touch_flag && cnt < TK_LONG_KEY_TIME) // 如果有按键按下（并且之前扫描到的不是长按）
    {
        // 通过循环判断是否为长按
        for (i = 0; i < 500000; i++) // 实际上用不到这么大的数字，到了设定的长按时间就会退出
        {
            // 按键扫描函数，使用了库里面的接口（闭源库）
            // 这个函数会更新__tk_key_flag的值
            delay_ms(10);
            __tk_scan();

            if (KeyOnOutput == __tk_key_flag)
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
                long_touch_flag = 1; // 标记为长按
                break;
            }
        }

        if (cnt > TK_LONG_KEY_TIME)
        {
            long_touch_flag = 1; // 标记为长按
        }
        else
        {
            // 如果是短按
            cnt = 0; // 清除长按的计数值

            // 判断当前触摸的键值，做对应的操作
            if (TK_CH24_VALIB == KeyOnOutput)
            {
                // 如果KEY1被触摸
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH24_VALIB == KeyOnOutput)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
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
            else if (TK_CH25_VALIB == KeyOnOutput)
            {
                // 如果KEY2被触摸
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH25_VALIB == KeyOnOutput)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
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
            else if (TK_CH23_VALIB == KeyOnOutput)
            {
                // 如果KEY3被触摸
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH23_VALIB == KeyOnOutput)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
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
            else if (TK_CH17_VALIB == KeyOnOutput)
            {
                // 如果KEY4被触摸
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH17_VALIB == KeyOnOutput)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
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
            else if (TK_CH15_VALIB == KeyOnOutput)
            {
                // 如果KEY5被触摸
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH15_VALIB == KeyOnOutput)
                    {
                        // 如果检测到是同一个按键按下，说明是双击
                        // 等待手指松开按键，不然发送完带有双击状态的键值后会再发送一次单击状态的键值
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
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

    if (1 == long_touch_flag && 0 != KeyOnOutput)
    {
        KeyOld = KeyOnOutput;

        // 如果之前是长按，现在还未松开
        // 判断当前触摸的键值，做对应的操作
        if (TK_CH24_VALIB == KeyOnOutput)
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
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

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
        else if (TK_CH25_VALIB == KeyOnOutput)
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
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

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
        else if (TK_CH23_VALIB == KeyOnOutput)
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
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

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
        else if (TK_CH17_VALIB == KeyOnOutput)
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
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

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
        else if (TK_CH15_VALIB == KeyOnOutput)
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
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

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
    else if (1 == long_touch_flag && 0 == KeyOnOutput)
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

        long_touch_flag = 0; // 清除标志位
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

/*************************** (C) COPYRIGHT 2022 TAIXIN-IC ***** END OF FILE *****/
