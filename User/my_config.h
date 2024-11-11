// my_config.h -- 自定义的配置文件
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h" // 使用芯片官方提供的头文件


// ============================================================
// 如果需要修改使用的触摸按键数量和位置，需要去tk_config.h中修改
// 并在tk_user.c中添加/修改对应的功能
// 触摸按键的数量和通道位置必须要一一对应
// ============================================================

#define USE_MY_DEBUG 1


// 开发板上使用P11作为发送键值信号的引脚
// 目标电路板上使用的是P21
// 如果需要修改，要去send_key.c中修改引脚相关的初始化配置函数
#define SEND_KEY_VAL_PIN            P11 // 发送键值信号的引脚





#include "uart0.h" // 调试用的串口
#include "aip650.h" 
#include "send_key.h"

#endif // end file
