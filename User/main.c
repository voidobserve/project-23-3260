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
#include <string.h>
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

    aip650_config();

    /* ������ʼ�� */
    tk_param_init();
    tmr0_config(); // ���ü�⴮�ڽ������ݳ�ʱ�Ķ�ʱ��
#if USE_MY_DEBUG
    uart0_config(); // ����ʹ�õ��Ĵ���
#endif
    uart1_config();

    /* ϵͳ��ѭ�� */
    while (1)
    {
        /* ����ɨ�躯�� */
        __tk_scan(); // ʹ���˿�����Ľӿڣ���Դ�⣩

        /* �û�ѭ��ɨ�躯���ӿ� */
        user_handle();
        uart1_recv_err_handle();

        if (flag_cur_recv_status == CUR_RECV_STATUS_COMPLETE)
        {
#if USE_MY_DEBUG
            printf("recv complete\n");

            printf("seg1 %#x\n", (u16)instruction.seg1);
            printf("seg2 %#x\n", (u16)instruction.seg2);
            printf("point %#x\n", (u16)instruction.point);
            printf("led %#x\n", (u16)instruction.led);
            // printf("addr  %p\n", &instruction);
#endif
            aip650_show_handle(instruction);

            memset(&instruction, 0xFF, sizeof(instruction)); // ��մ��ָ��Ľṹ�����
            flag_cur_recv_status = CUR_RECV_STATUS_NONE;     // ���������ɱ�־
        }

        // /* ι�� :���鲻Ҫ�رտ��Ź���Ĭ��2s��λ*/
        // WDT_KEY = WDT_KEY_VAL(0xAA);
    }
}

/**
 * @}
 */

/*************************** (C) COPYRIGHT 2022 HUGE-IC ***** END OF FILE *****/
