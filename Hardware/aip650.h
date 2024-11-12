#ifndef __AIP650_H
#define __AIP650_H

#include "include.h" // 包含芯片官方提供的头文件
#include "my_config.h"

extern u8 aip650_show_buff[3];         // aip650显示缓冲区（显存）
extern const u8 aip650_data_map_buf[]; //

extern void aip650_config(void);
extern void aip650_show_handle(instruction_t); 
extern void aip650_show_refresh(void);
// extern void aip650_show_handle(instruction_t instruction); // 使用这个声明，编译会不通过

#endif
