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
// xdata u16 led_data[1];                           // LED��ʾbuff
#define LED_DIS_FREQ (1000000 / 16 / 8 / 60 - 1) // һ��CON����ʾʱ��60Hz    60-1=1M/(LED_COMCON*16*LED_TIME_CON)

unsigned int xdata display_data = 0;

/**
 * @brief  ���Խӿ�IO��ʼ������.
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
 * @brief  �û�����ѭ��ִ�к����ӿ�.����������ɨ�躯���ӿڣ�
 * @param  None
 * @retval None
 */
#define send_sp (100)
void user_handle(void)
{
    volatile unsigned long int KeyOnOutput = __tk_key_flag; // __tk_key_flag���ΰ�����־

    static volatile unsigned long int KeyOld = 0; // ���ڴ�ų���ʱ����Ӧ�İ���

    // �Ƿ񳤰��ı�־��0--��1--��
    // ��Ҫ���泤����״̬����ʾ��ʱ��һֱ�ڷ��ͼ�ֵ
    static unsigned char long_touch_flag = 0; // ��һ��ɨ�赽�İ����Ƿ�Ϊ�����ı�־

    static volatile u32 cnt = 0; // ��������ֵ

    u32 i = 0; // ѭ������ֵ

    u16 send_data = 0; // Ҫ���͵Ĵ��м�ֵ������

    if (KeyOnOutput && 0 == long_touch_flag && cnt < TK_LONG_KEY_TIME) // ����а������£�����֮ǰɨ�赽�Ĳ��ǳ�����
    {
        // ͨ��ѭ���ж��Ƿ�Ϊ����
        for (i = 0; i < 500000; i++) // ʵ�����ò�����ô������֣������趨�ĳ���ʱ��ͻ��˳�
        {
            // ����ɨ�躯����ʹ���˿�����Ľӿڣ���Դ�⣩
            // ������������__tk_key_flag��ֵ
            delay_ms(10);
            __tk_scan();

            if (KeyOnOutput == __tk_key_flag)
            {
                // ���������ֵһ�£�˵������һֱ�����£�δ�ɿ�
                cnt++;
            }
            else
            {
                // ���������ֵ��һ�»����ɿ��˰���
                // cnt = 0;
                break;
            }
            
            if (cnt > TK_LONG_KEY_TIME) // ��������������������õ�ʱ��
            {
                long_touch_flag = 1; // ���Ϊ����
                break;
            }
        }

        if (cnt > TK_LONG_KEY_TIME)
        {
            long_touch_flag = 1; // ���Ϊ����
        }
        else
        {
            // ����Ƕ̰�
            cnt = 0; // ��������ļ���ֵ

            // �жϵ�ǰ�����ļ�ֵ������Ӧ�Ĳ���
            if (TK_CH24_VALIB == KeyOnOutput)
            {
                // ���KEY1������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH24_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
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

// �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k1 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY1); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH25_VALIB == KeyOnOutput)
            {
                // ���KEY2������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH25_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
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

// �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k2 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY2); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH23_VALIB == KeyOnOutput)
            {
                // ���KEY3������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH23_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
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

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k3 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY3); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH17_VALIB == KeyOnOutput)
            {
                // ���KEY4������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH17_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
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

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k4 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY4); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH15_VALIB == KeyOnOutput)
            {
                // ���KEY5������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH15_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
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

// �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k5 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY5); // ���ʹ���״̬�ļ�ֵ
            }
        }
    }

    if (1 == long_touch_flag && 0 != KeyOnOutput)
    {
        KeyOld = KeyOnOutput;

        // ���֮ǰ�ǳ��������ڻ�δ�ɿ�
        // �жϵ�ǰ�����ļ�ֵ������Ӧ�Ĳ���
        if (TK_CH24_VALIB == KeyOnOutput)
        {
            // ���KEY1������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k1 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY1);
            }

            // �������ɿ��֣���ÿ��150ms����һ�δ��г���״̬��Ϣ�ļ�ֵ�ź�
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

                if (cnt >= 87) // ԭ������90�ģ����������ʱ��������ֻ����������
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
            // ���KEY2������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k2 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY2);
            }

            // �������ɿ��֣���ÿ��150ms����һ�δ��г���״̬��Ϣ�ļ�ֵ�ź�
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

                if (cnt >= 87) // ԭ������90�ģ����������ʱ��������ֻ����������
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k2 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY2);
                }
            }

            // display_data ^= 0x0200; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
        else if (TK_CH23_VALIB == KeyOnOutput)
        {
            // ���KEY3������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
#if USE_MY_DEBUG
                printf("k3 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY3);
            }

            // �������ɿ��֣���ÿ��150ms����һ�δ��г���״̬��Ϣ�ļ�ֵ�ź�
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

                if (cnt >= 87) // ԭ������90�ģ����������ʱ��������ֻ����������
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
            // ���KEY4������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
#if USE_MY_DEBUG
                printf("k4 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY4);
            }

            // �������ɿ��֣���ÿ��150ms����һ�δ��г���״̬��Ϣ�ļ�ֵ�ź�
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

                if (cnt >= 87) // ԭ������90�ģ����������ʱ��������ֻ����������
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k4 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY4);
                }
            }

            // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
        else if (TK_CH15_VALIB == KeyOnOutput)
        {
            // ���KEY5������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
#if USE_MY_DEBUG
                printf("k5 long press\n");
#endif
                send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY5);
            }

            // �������ɿ��֣���ÿ��150ms����һ�δ��г���״̬��Ϣ�ļ�ֵ�ź�
            while (0 != KeyOnOutput)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                KeyOnOutput = __tk_key_flag;

                if (cnt >= 87) // ԭ������90�ģ����������ʱ��������ֻ����������
                {
                    cnt = TK_LONG_KEY_TIME;
#if USE_MY_DEBUG
                    printf("k5 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY5);
                }
            }

            // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
    }
    else if (1 == long_touch_flag && 0 == KeyOnOutput)
    {
        // ���֮ǰ�ǳ���������ȴ�ɿ��˰���
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

        long_touch_flag = 0; // �����־λ
        cnt = 0;
        KeyOld = 0;
    }

#if 0
    if (1 == __tk_long_key_flag) // �������������������ܲ��Է��ֲ��У������ã�
    {
        __tk_long_key_flag = 0;

        // ��������Լ���������Լ���Ҫ�Ĺ���

        P11 = 0;
    }
#endif
}

/*************************** (C) COPYRIGHT 2022 TAIXIN-IC ***** END OF FILE *****/
