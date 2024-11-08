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

// void iic_config(void)
// {
//     // IIC IO口配置开漏上拉: iic_data--P22(AF1)   iic_clk--P21(AF1)
//     // P2_MD0 &= ~(GPIO_P21_MODE_SEL(0x3) | GPIO_P22_MODE_SEL(0x3)); // 配置P00/P01为复用模式
//     // P2_MD0 |= (GPIO_P21_MODE_SEL(0x2) | GPIO_P22_MODE_SEL(0x2));
//     // P2_PU |= (GPIO_P21_PULL_UP(0x1) | GPIO_P22_PULL_UP(0x1));    // 上拉
//     // P2_ODN |= (GPIO_P21_ODN_EN(0x1) | GPIO_P22_ODN_EN(0x1));     // 开漏
//     // P2_AF0 |= (GPIO_P21_FUNC_SEL(0x1) | GPIO_P22_FUNC_SEL(0x1)); // 配置P21为clk线，P22为data线

// }

void main(void)
{
    // 看门狗默认打开, 复位时间2s
    system_init();

    WDT_KEY = WDT_KEY_VAL(0xDD); //  关闭看门狗

    // 关闭HCK和HDA的调试功能:
    WDT_KEY = 0x55;
    IO_MAP &= ~0x01;
    WDT_KEY = 0xBB;

    /* 用户代码初始化接口 */
    user_init();
    // iic_config();
    aip650_config();
    aip650e_init(&sg_650e_drv);


    /* 按键初始化 */
    // tk_param_init();

    /* 系统主循环 */
    while (1)
    {
        /* 按键扫描函数 */
        // __tk_scan(); // 使用了库里面的接口（闭源库）

        /* 用户循环扫描函数接口 */
        // user_handle();

        // iic_master_tx(0x48, 1);
        // iic_master_tx(0x00, 0);

        // iic_master_tx(0x48, 0);
        // iic_master_tx(0x01, 0);            

        // iic_master_tx(0x68, 0);
        // iic_master_tx(0xFF, 0);

        // iic_master_tx(0x6A, 0);
        // iic_master_tx(0xFF, 0);

        // iic_master_tx(0x6C, 0);
        // iic_master_tx(0xFF, 0);

        // iic_master_tx(0x6E, 0);
        // iic_master_tx(0xFF, 2);

        test_aip650e();
        delay_ms(500);

        // /* 喂狗 :建议不要关闭看门狗，默认2s复位*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
