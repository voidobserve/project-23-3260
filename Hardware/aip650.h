#ifndef __AIP650_H
#define __AIP650_H

#include "include.h" // 包含芯片官方提供的头文件
#include "my_config.h" 
 
extern u8 aip650_show_buff[3]; // aip650显示缓冲区（显存）

extern const u8 aip650_data[];

extern void aip650_config(void);

// extern void aip650_show_buff_update(u8 *buff); // 更新aip650的显存
extern void aip650_show_refresh(void);      // 刷新aip650要显示的内容(将aip650显存的内容更新到外设上)

extern void aip650_show_data(u8 num_bit1, u8 num_bit0);// 向aip650的显存写入要显示的数字
extern void aip650_show_point(u8 locate); // 向aip650显存写入要显示的小数点
extern void aip650_show_led_of_touch(u8 led_data); // 向aip650显存写入要点亮的触摸按键的对应的LED

#endif

