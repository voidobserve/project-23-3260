// my_config.h -- 自定义的配置文件
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h" // 使用芯片官方提供的头文件

// ============================================================
// 如果需要修改使用的触摸按键数量和位置，需要去tk_config.h中修改
// 并在tk_user.c中添加/修改对应的功能
// 触摸按键的数量和通道位置必须要一一对应
// ============================================================

#define USE_MY_DEBUG 0
#include <stdio.h>

// 发送键值信号的引脚
// 如果需要修改，要去send_key.c中修改引脚相关的初始化配置函数
#define SEND_KEY_VAL_PIN P11 // 发送键值信号的引脚

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))

#define TOUCH_KEY_ID_1 TK_CH24_VALIB // 按键标识--触摸按键K1
#define TOUCH_KEY_ID_2 TK_CH25_VALIB // 按键标识--触摸按键K2
#define TOUCH_KEY_ID_3 TK_CH23_VALIB // 按键标识--触摸按键K3
#define TOUCH_KEY_ID_4 TK_CH17_VALIB // 按键标识--触摸按键K4
#define TOUCH_KEY_ID_5 TK_CH15_VALIB // 按键标识--触摸按键K5

#define DETECT_DOUBLE_CLICK_INTERVAL (100) // 检测双击的时间间隔(单位：ms)
#define LONG_PRESS_TIME_THRESHOLD_MS (750) // 长按时间阈值（单位：ms）
#define HOLD_PRESS_TIME_THRESHOLD_MS (150) // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件
#define LOOSE_PRESS_CNT_MS (50)           // 松手计时，松开手多久，才认为是真的松手了
#define ONE_CYCLE_TIME_MS (0)              // 主函数完成一次循环所需的时间，单位：ms (0--说明每次调用该函数的时间很短，可以忽略不计)

#include "tmr0.h"  // 检测串口接收超时的定时器
#include "uart0.h" // 调试用的串口
#include "uart1.h" // 接收指令的串口
#include "aip650.h"
#include "send_key.h" // 发送键值的相关接口，内部使用了tmr1定时器

#endif // end file
