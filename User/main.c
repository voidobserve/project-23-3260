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
 * ��Ȩ˵����������
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
//     // IIC IO�����ÿ�©����: iic_data--P22(AF1)   iic_clk--P21(AF1)
//     // P2_MD0 &= ~(GPIO_P21_MODE_SEL(0x3) | GPIO_P22_MODE_SEL(0x3)); // ����P00/P01Ϊ����ģʽ
//     // P2_MD0 |= (GPIO_P21_MODE_SEL(0x2) | GPIO_P22_MODE_SEL(0x2));
//     // P2_PU |= (GPIO_P21_PULL_UP(0x1) | GPIO_P22_PULL_UP(0x1));    // ����
//     // P2_ODN |= (GPIO_P21_ODN_EN(0x1) | GPIO_P22_ODN_EN(0x1));     // ��©
//     // P2_AF0 |= (GPIO_P21_FUNC_SEL(0x1) | GPIO_P22_FUNC_SEL(0x1)); // ����P21Ϊclk�ߣ�P22Ϊdata��

// }

void main(void)
{
    // ���Ź�Ĭ�ϴ�, ��λʱ��2s
    system_init();

    WDT_KEY = WDT_KEY_VAL(0xDD); //  �رտ��Ź�

    // �ر�HCK��HDA�ĵ��Թ���:
    WDT_KEY = 0x55;
    IO_MAP &= ~0x01;
    WDT_KEY = 0xBB;

    /* �û������ʼ���ӿ� */
    user_init();
    // iic_config();
    aip650_config();
    aip650e_init(&sg_650e_drv);


    /* ������ʼ�� */
    // tk_param_init();

    /* ϵͳ��ѭ�� */
    while (1)
    {
        /* ����ɨ�躯�� */
        // __tk_scan(); // ʹ���˿�����Ľӿڣ���Դ�⣩

        /* �û�ѭ��ɨ�躯���ӿ� */
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

        // /* ι�� :���鲻Ҫ�رտ��Ź���Ĭ��2s��λ*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
