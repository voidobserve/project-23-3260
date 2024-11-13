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
// // xdata u16 led_data[1];                           // LED��ʾbuff
// #define LED_DIS_FREQ (1000000 / 16 / 8 / 60 - 1) // һ��CON����ʾʱ��60Hz    60-1=1M/(LED_COMCON*16*LED_TIME_CON)

// unsigned int xdata display_data = 0;

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

#if 0
/**
 * @brief  �û�����ѭ��ִ�к����ӿ�.����������ɨ�躯���ӿڣ�
 * @param  None
 * @retval None
 */
#define DETECT_DOUBLE_CLICK_INTERVAL (100) // ���ͼ��
void user_handle(void)
{
    volatile unsigned long int touch_key = __tk_key_flag; // __tk_key_flag���ΰ�����־

    static volatile unsigned long int KeyOld = 0; // ���ڴ�ų���ʱ����Ӧ�İ���

    // �Ƿ񳤰��ı�־��0--��1--��
    // ��Ҫ���泤����״̬����ʾ��ʱ��һֱ�ڷ��ͼ�ֵ
    static unsigned char flag_is_long_press = 0; // ��һ��ɨ�赽�İ����Ƿ�Ϊ�����ı�־

    static volatile u32 cnt = 0; // ��������ֵ

    u32 i = 0; // ѭ������ֵ

    u16 send_data = 0; // Ҫ���͵Ĵ��м�ֵ������

    if (touch_key && 0 == flag_is_long_press && cnt < TK_LONG_KEY_TIME) // ����а������£�����֮ǰɨ�赽�Ĳ��ǳ�����
    {
        // ͨ��ѭ���ж��Ƿ�Ϊ����
        for (i = 0; i < 500000; i++) // ʵ�����ò�����ô������֣������趨�ĳ���ʱ��ͻ��˳�
        {
            // ����ɨ�躯����ʹ���˿�����Ľӿڣ���Դ�⣩
            // ������������__tk_key_flag��ֵ
            delay_ms(10);
            __tk_scan();

            if (touch_key == __tk_key_flag)
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
                flag_is_long_press = 1; // ���Ϊ����
                break;
            }
        }

        if (cnt > TK_LONG_KEY_TIME)
        {
            flag_is_long_press = 1; // ���Ϊ����
        }
        else
        {
            // ����Ƕ̰�
            cnt = 0; // ��������ļ���ֵ

            // �жϵ�ǰ�����ļ�ֵ������Ӧ�Ĳ���
            if (TK_CH24_VALIB == touch_key)
            {
                // ���KEY1������
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH24_VALIB == touch_key)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
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
            else if (TK_CH25_VALIB == touch_key)
            {
                // ���KEY2������
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH25_VALIB == touch_key)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
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
            else if (TK_CH23_VALIB == touch_key)
            {
                // ���KEY3������
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH23_VALIB == touch_key)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
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
            else if (TK_CH17_VALIB == touch_key)
            {
                // ���KEY4������
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH17_VALIB == touch_key)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
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
            else if (TK_CH15_VALIB == touch_key)
            {
                // ���KEY5������
                for (i = 0; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    touch_key = __tk_key_flag;

                    if (TK_CH15_VALIB == touch_key)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != touch_key)
                        {
                            __tk_scan();
                            touch_key = __tk_key_flag;
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

    if (1 == flag_is_long_press && 0 != touch_key)
    {
        KeyOld = touch_key;

        // ���֮ǰ�ǳ��������ڻ�δ�ɿ�
        // �жϵ�ǰ�����ļ�ֵ������Ӧ�Ĳ���
        if (TK_CH24_VALIB == touch_key)
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
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

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
        else if (TK_CH25_VALIB == touch_key)
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
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

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
        else if (TK_CH23_VALIB == touch_key)
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
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

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
        else if (TK_CH17_VALIB == touch_key)
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
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

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
        else if (TK_CH15_VALIB == touch_key)
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
            while (0 != touch_key)
            {
                delay_ms(10);
                cnt++;
                __tk_scan();
                touch_key = __tk_key_flag;

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
    else if (1 == flag_is_long_press && 0 == touch_key)
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

        flag_is_long_press = 0; // �����־λ
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
#endif

/**
 * @brief __is_double_click() �ж��Ƿ���˫��ͬһ����������,�ڲ����ʱʱ�䣺DETECT_DOUBLE_CLICK_INTERVAL
 *
 * @param touch_key_id_const
 * @return u8 0--û��˫��ͬһ������������1--˫����ͬһ����������
 */
u8 __is_double_click(const u32 touch_key_id_const)
{
    u8 i = 0;                   // ѭ������ֵ
    volatile u32 touch_key = 0; // ���ÿ�μ�⵽�İ���

    for (; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
    {
        delay_ms(1);
        __tk_scan();
        touch_key = __tk_key_flag;

        if (touch_key_id_const == touch_key)
        {
            // �����⵽��ͬһ���������£�˵����˫��
            return 1; // ˫����ͬһ����������������1
        }
    }

    return 0; // û��˫��ͬһ����������������0
}

enum
{
    TOUCH_KEY_SCAN_STATUS_NONE,                  // ��״̬������Ƿ��а�������
    TOUCH_KEY_SCAN_STATUS_IS_DETECT_LOOG_PRESS,  // ���ڼ���Ƿ�Ϊ������Ҫ����ⳤ�������֣�
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS,  // ���ڴ�����
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS,  // ���ڴ����������������֣�
    TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS, // ���ڴ���̰�

    TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE, // ���ڵȴ��̰��ɿ�
    TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE,  // ���ڵȴ������ɿ�
    TOUCH_KEY_SCAN_STATUS_IS_END,                      // ��β����
};

static volatile u8 touch_key_scan_status = 0; // �������İ���ɨ�躯���У�ʹ�õ�״̬��

// �������İ���ɨ�躯��
void touch_key_scan(void)
{
    volatile u32 touch_key = 0;             // __tk_key_flag ���ΰ�����־
    static u32 touch_key_last = 0;          // ���ڴ�ų���ʱ����Ӧ�İ���
    static volatile u32 touch_time_cnt = 0; // ��������ֵ

    /* ����ɨ�躯�� */
    __tk_scan();               // ʹ���˿�����Ľӿڣ���Դ�⣩
    touch_key = __tk_key_flag; // __tk_key_flag ���ΰ�����־

    if (TOUCH_KEY_SCAN_STATUS_NONE == touch_key_scan_status) // δ��⵽����ʱ
    {
        // ����а������£�����֮ǰɨ�赽�Ĳ��ǳ�����
        // if (touch_key && touch_time_cnt < LONG_PRESS_TIME_THRESHOLD_MS)
        // if (touch_key)
        // if (touch_key_last != touch_key && touch_key != 0)
        {
            // �ж��Ƿ�Ϊ������

            if (touch_key_last == 0) // ���֮ǰδ��⵽����
            {
                touch_key_last = touch_key;
            }
            else if (touch_key_last == touch_key)
            {
                // ����ϴμ�⵽�İ�����˴εİ�����ȣ�˵��������δ�ɿ�
                touch_time_cnt += (1 + ONE_CYCLE_TIME_MS);

                if (touch_time_cnt >= LONG_PRESS_TIME_THRESHOLD_MS)
                {
                    // ����������������õĳ���ʱ��
                    // ��ת����������
                    touch_time_cnt = 0; // �������ʱ�����

                    printf("long press\n");
                    touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS;
                }
            }
            else
            {
                // ����ϴμ�⵽�İ�����˴εİ�������ȣ������ϴμ�⵽�İ���������0
                // touch_time_cnt = 0; // �������ʱ�����������������β����

                // ��ת���̰�����
                touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS;

                // printf("short press\n");
            }

            delay_ms(1); //
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS == touch_key_scan_status)
    {
        // ��������ڴ���̰�
        bit flag_is_double_click = 0; // ��־λ���Ƿ��а���˫��

        if (TOUCH_KEY_ID_1 == touch_key_last)
        {
            // ���KEY1������
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // ����а���˫��
#if USE_MY_DEBUG
                printf("k1 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY1); // ���ʹ���״̬�ļ�ֵ
            }
            else
            {
                // ���û�а���˫����˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k1 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY1); // ���ʹ���״̬�ļ�ֵ
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // �ȴ������ɿ�
        }
        else if (TOUCH_KEY_ID_2 == touch_key_last)
        {
            // ���KEY2������
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // ����а���˫��
#if USE_MY_DEBUG
                printf("k2 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY2); // ���ʹ���״̬�ļ�ֵ
            }
            else
            {
                // ���û�а���˫����˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k2 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY2); // ���ʹ���״̬�ļ�ֵ
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // �ȴ������ɿ�
        }
        else if (TOUCH_KEY_ID_3 == touch_key_last)
        {
            // ���KEY3������
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // ����а���˫��
#if USE_MY_DEBUG
                printf("k3 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY3); // ���ʹ���״̬�ļ�ֵ
            }
            else
            {
                // ���û�а���˫����˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k3 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY3); // ���ʹ���״̬�ļ�ֵ
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // �ȴ������ɿ�
        }
        else if (TOUCH_KEY_ID_4 == touch_key_last)
        {
            // ���KEY4������
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // ����а���˫��
#if USE_MY_DEBUG
                printf("k4 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY4); // ���ʹ���״̬�ļ�ֵ
            }
            else
            {
                // ���û�а���˫����˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k4 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY4); // ���ʹ���״̬�ļ�ֵ
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // �ȴ������ɿ�
        }
        else if (TOUCH_KEY_ID_5 == touch_key_last)
        {
            // ���KEY5������
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // ����а���˫��
#if USE_MY_DEBUG
                printf("k5 double press\n");
#endif
                send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY5); // ���ʹ���״̬�ļ�ֵ
            }
            else
            {
                // ���û�а���˫����˵���Ƕ̰�
#if USE_MY_DEBUG
                printf("k5 press\n");
#endif
                send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY5); // ���ʹ���״̬�ļ�ֵ
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // �ȴ������ɿ�
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS == touch_key_scan_status)
    {
        // ������
        if (TOUCH_KEY_ID_1 == touch_key)
        {
            // ���KEY1������

#if USE_MY_DEBUG
            printf("k1 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY1);
        }
        else if (TOUCH_KEY_ID_2 == touch_key)
        {
            // ���KEY2������

#if USE_MY_DEBUG
            printf("k2 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY2);
        }
        else if (TOUCH_KEY_ID_3 == touch_key)
        {
            // ���KEY3������

#if USE_MY_DEBUG
            printf("k3 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY3);
        }
        else if (TOUCH_KEY_ID_4 == touch_key)
        {
            // ���KEY4������

#if USE_MY_DEBUG
            printf("k4 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY4);
        }
        else if (TOUCH_KEY_ID_5 == touch_key)
        {
            // ���KEY5������

#if USE_MY_DEBUG
            printf("k5 long press\n");
#endif
            send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY5);
        }

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS; // ��ת����������
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS == touch_key_scan_status)
    {
        // ����������

        if (touch_key_last == touch_key)
        {
            touch_time_cnt++;
            if (TOUCH_KEY_ID_1 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k1 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY1);
                }
            }
            else if (TOUCH_KEY_ID_2 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k2 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY2);
                }
            }
            else if (TOUCH_KEY_ID_3 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k3 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY3);
                }
            }
            else if (TOUCH_KEY_ID_4 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k4 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY4);
                }
            }
            else if (TOUCH_KEY_ID_5 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
#if USE_MY_DEBUG
                    printf("k5 continue press\n");
#endif
                    send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY5);
                }
            }

            delay_ms(1);
        }
        else
        {
            // ���֮ǰ��⵽�İ����뵱ǰ��⵽�İ�����һ�£�
            // ˵�� �����ɿ����� ���� һֻ�ְ�ס��ԭ���İ�����һֻ�ְ�����������

            // ��ת���ȴ������ɿ�
            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE;
        }
    }

    if ((TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status) ||
        (TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE == touch_key_scan_status))
    {
        // ����ǵȴ������ɿ�
        static volatile u16 loose_cnt = 0; // ������ּ���ֵ

        if (touch_key == 0)
        {
            loose_cnt++;
            delay_ms(1);
        }
        else
        {
            // ֻҪ��һ�μ�⵽������˵��û���ɿ���
            loose_cnt = 0;
        }

        if (loose_cnt >= LOOSE_PRESS_CNT_MS) // ����ıȽ�ֵ��Ҫע�⣬���ܴ��ڱ������Ͷ�Ӧ�����ֵ
        {
            loose_cnt = 0; // ������ּ���
            // ��� xx ms��û�м�⵽�������£�˵���Ѿ��ɿ���

            if (TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status)
            {
                if (TOUCH_KEY_ID_1 == touch_key_last)
                {
#if USE_MY_DEBUG
                    printf("k1 long press loose\n");
#endif
                    send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY1);
                }
            }


            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_END; // ��ת����β����
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_END == touch_key_scan_status)
    {
        // ��β����
        touch_key = 0;
        touch_key_last = 0;
        touch_time_cnt = 0;

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_NONE;
    }
}

/*************************** (C) COPYRIGHT 2022 TAIXIN-IC ***** END OF FILE *****/
