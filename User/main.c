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
    // ���Ź�Ĭ�ϴ�, ��λʱ��2s
    system_init();

    WDT_KEY = WDT_KEY_VAL(0xDD); //  �رտ��Ź�

    // �ر�HCK��HDA�ĵ��Թ���:
    WDT_KEY = 0x55;
    IO_MAP &= ~0x01;
    WDT_KEY = 0xBB;

    send_keyval_pin_init();   // ��ʼ����ֵ�ķ�������
    send_keyval_timer_init(); // ��ʼ�����ͼ�ֵ��������ʹ�õ��Ķ�ʱ������ʱ��Ĭ�Ϲر�

    // tmr1_enable(); // �򿪷��ͼ�ֵ��������ʹ�õ��Ķ�ʱ���������ã�������ʱ���ж��Ƿ����õ�ʱ�䴥��

    // tmr3_config(); // ���ö�ʱ����ÿ10ms����һ���жϣ���Ӧ�ļ���ֵ+1�������жϰ����Ķ̰��������ͳ���

    aip650_config();

    /* ������ʼ�� */
    tk_param_init();

    uart0_config(); // ����ʹ�õ��Ĵ���

    /* ϵͳ��ѭ�� */
    while (1)
    {
        /* ����ɨ�躯�� */
        __tk_scan(); // ʹ���˿�����Ľӿڣ���Դ�⣩

        /* �û�ѭ��ɨ�躯���ӿ� */
        user_handle();

        // aip650_show_data(14, 15);
        // aip650_show_refresh();
        // delay_ms(500);

        // aip650_show_buff[1] = 0x80;

        // aip650_show_led_of_touch(0x1F);
        // aip650_show_refresh();
        // delay_ms(500);

        // /* ι�� :���鲻Ҫ�رտ��Ź���Ĭ��2s��λ*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
