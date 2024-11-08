#ifndef __AIP650_H
#define __AIP650_H

#include "include.h" // 包含芯片官方提供的头文件
#include "my_config.h"

#define AIP650E_SIZE 4
 
struct _650e_drv_
{
    // 用户数据
    u8 temp;       // 数码管显示  50 60 90 120
 
    u8 _buf[AIP650E_SIZE]; // 数据存储
};
 
extern struct _650e_drv_ sg_650e_drv;
#define GET_650E() (&sg_650e_drv)
 
extern void aip650e_init(struct _650e_drv_ *drv);           // 初始化
extern void aip650e_display_update(struct _650e_drv_ *drv); // 屏显数据更新
extern void aip650e_update(struct _650e_drv_ *drv);         // 执行刷新
 
/*测试模式定义 -- 如需开启测试模式, 请打开下面的宏定义*/
#define AIP650_TEST_MODE
#ifdef AIP650_TEST_MODE
extern void test_aip650e(void);
#endif
 

extern void aip650_config(void);
extern  u8 iic_master_tx(u8 iic_data, u8 flag);

#endif