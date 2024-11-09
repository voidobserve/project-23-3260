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
#include "include.h"
#include "my_gpio.h"  // �Զ���ġ�ʹ�õ�������
// #include "rf_recv.h"  // RF315�����RF����������صĺ���
#include "send_key.h" // ���ͼ�ֵ�����ź���غ���

// #include "rf_learn.h" // rfѧϰ��صĺ���

#include "tmr2.h"
#include "tmr3.h"
// #include "rf_scan.h" // �����˳��̰���Ϣ�Ķ���

#include "key_conversion.h" // �����˴���������Ӧ�ļ�ֵ

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
xdata u16 led_data[1];                           // LED��ʾbuff
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
 * @brief  LED INIT FUNCTION
 * @param  None
 * @retval None
 */
// �ڿ������ϣ�
// P2_7���ӵ��ĸ���ɫLED�ĸ����Ĺ�����
// P0_3���ӵ�LED1����
// P3_0���ӵ�LED2����
// P1_0���ӵ�LED3����
// P0_7���ӵ�LED4����
void led_init(void)
{
    // ����COM0   P27Ϊ���ģʽ
    // P2_MD1��P2�Ĺ���ģʽ�Ĵ���1
    P2_MD1 &= ~GPIO_P27_MODE_SEL(0x3); // ����P2_MD1�Ĵ�����6-7λ
    P2_MD1 |= GPIO_P27_MODE_SEL(0x1);  // P2_MD1��6~7λ����Ϊ0x01�������ὫP2�ĵ�7��IO����Ϊ���ģʽ

    // ����IO����������
    // P2�ĵ�7��IO����������Ϊ8mA
    P2_DRV7 = GPIO_P27_DRV_SEL(0x1);

    // ����SEG0-SEG4 P03\P30\P10\P07-���ģʽ
    // P0_3��P3_0��P1_0��P0_1����Ϊ���ģʽ
    // �����������㣬����λ�Ĳ���
    P0_MD0 &= ~GPIO_P03_MODE_SEL(0x3);
    P3_MD0 &= ~GPIO_P30_MODE_SEL(0x3);
    P1_MD0 &= ~GPIO_P10_MODE_SEL(0x3);
    P0_MD1 &= ~GPIO_P07_MODE_SEL(0x3);

    P0_MD0 |= GPIO_P03_MODE_SEL(0x1);
    P3_MD0 |= GPIO_P30_MODE_SEL(0x1);
    P1_MD0 |= GPIO_P10_MODE_SEL(0x1);
    P0_MD1 |= GPIO_P07_MODE_SEL(0x1);

    // SEG0-SEG4 P03\P30\P10\P07
    // ����P0_3��P3_0��P1_0��P0_1��������ܣ�����LED��Ӧ�������ӵ���Ƭ������LEDģ�飬���ģ���Ǹ���������
    FOUT_S03 = GPIO_FOUT_LED_SEG0;
    FOUT_S30 = GPIO_FOUT_LED_SEG1;
    FOUT_S10 = GPIO_FOUT_LED_SEG2;
    FOUT_S07 = GPIO_FOUT_LED_SEG3;

    // ����P0_3��P3_0��P1_0��P0_1�����������8mA
    P0_DRV3 = GPIO_P03_DRV_SEL(0x1);
    P3_DRV0 = GPIO_P30_DRV_SEL(0x1);
    P1_DRV0 = GPIO_P10_DRV_SEL(0x1);
    P0_DRV7 = GPIO_P07_DRV_SEL(0x1);

    // COM0 P27
    // ����P2_7��������ܣ����ӵ�LED�Ĺ�����0
    FOUT_S27 = GPIO_FOUT_LED_COM0;

    CLK_CON2 |= CLK_LED_EN(0x1); // ��LEDģ���ʱ�ӣ���Ƭ������LEDģ���ʱ�ӣ�

    // 0x55��ʾ������ʺ����� wdt_psr����WDT_CON�У�psr��ʾ���Ź���ʱʱ�䣩
    WDT_KEY = 0x55;                // ����IO_MAP�Ĵ�����ҪдKEY
    IO_MAP |= MAP_LED_DMA_EN(0x1); // LED DMAʹ��
    WDT_KEY = 0xBB;                // д��һ���������ֵ���ָ��üĴ�����д����

    // ��LEDģ���ʱ��
    CLK_CON2 |= 0x10;

    LED_SEGCONL = LED_SEG0_EN(0x1) | // SEG0 ʹ��
                  LED_SEG1_EN(0x1) | // SEG0 ʹ��
                  LED_SEG2_EN(0x1) | // SEG0 ʹ��
                  LED_SEG3_EN(0x1);  // SEG0 ʹ��
    LED_COMCON = LED_COM0_EN(0x1);   // COM1 ʹ��

    LED_DMAADRH = LED_DMA_ADDR_H((((u16)led_data) >> 8) & 0xFF); // LED���ݴ����׵�ַ�ĸ�8λ
    LED_DMAADRL = LED_DMA_ADDR_L((((u16)led_data) >> 0) & 0xFF); // LED���ݴ����׵�ַ�ĵ�8λ
    LED_TIMECON = LED_SCAN_TIME(LED_DIS_FREQ);                   // ɨ�赽ĳ��com��segʱ������ʱ��,����Ϊ32΢��
    LED_CON = LED_COM_SEG_SEL(0x0) |                             // ɨ�跽ʽѡ��comɨ��
              LED_EN(0x1);                                       // LEDʹ��,ʹ��֮���DMAADDRH��DMAADDRL�ĵ�ַ��ʼ������ɨ�����,�û�������д����Ӧ�ĵ�ַ����

    led_data[0] = 0x00000f00; // һ��ʼ���ĸ�LEDȫ������
    // led_data[0] = 0x00000000; // һ��ʼ���ĸ�LEDȫ��Ϩ��
}

/**
 * @brief  �û������ʼ�������ӿ�.
 * @param  None
 * @retval None
 */
void user_init(void)
{
    // led_init(); // ��ʼ��LED��ص�����

    // rfin_init(); // RF315�������ų�ʼ��������Ҳ��ʼ����tmr0

    // p12_output_config(); // �����ã�P12��ʼ��������Ϊ���ģʽ

    // send_keyval_pin_init();   // ��ʼ����ֵ�ķ�������
    // send_keyval_timer_init(); // ��ʼ�����ͼ�ֵ��������ʹ�õ��Ķ�ʱ������ʱ��Ĭ�Ϲر�

    // tmr0_enable(); // �򿪲ɼ�RF�źŵĶ�ʱ��
    // // tmr1_enable(); // �򿪷��ͼ�ֵ��������ʹ�õ��Ķ�ʱ���������ã�������ʱ���ж��Ƿ����õ�ʱ�䴥��

    // tmr2_config(); // �ϵ�5s�ڵ�"ѧϰ"��ʹ�õĶ�ʱ��
    // tmr3_config(); // ���ö�ʱ����ÿ10ms����һ���жϣ���Ӧ�ļ���ֵ+1�������жϰ����Ķ̰��������ͳ���
    // tmr4_config(); // ��ʶ��ң����˫������Ҫ�Ķ�ʱ��

    // p01_output_config(); // ������LED6��Ӧ�����ų�ʼ��
    // p26_output_config(); // ������LED7��Ӧ�����ų�ʼ��
}

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

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK1);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK1); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH3_VALIB == KeyOnOutput)
            {
                // ���KEY2������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH3_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
                        }

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK2);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK2); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH2_VALIB == KeyOnOutput)
            {
                // ���KEY3������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH2_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
                        }

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK3);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK3); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH0_VALIB == KeyOnOutput)
            {
                // ���KEY4������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH0_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
                        }

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK4);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK4); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH9_VALIB == KeyOnOutput)
            {
                // ���KEY5������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH9_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
                        }

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK5);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK5); // ���ʹ���״̬�ļ�ֵ
            }
            else if (TK_CH10_VALIB == KeyOnOutput)
            {
                // ���KEY6������
                for (i = 0; i < send_sp; i++)
                {
                    delay_ms(1);
                    __tk_scan();
                    KeyOnOutput = __tk_key_flag;

                    if (TK_CH10_VALIB == KeyOnOutput)
                    {
                        // �����⵽��ͬһ���������£�˵����˫��
                        // �ȴ���ָ�ɿ���������Ȼ���������˫��״̬�ļ�ֵ����ٷ���һ�ε���״̬�ļ�ֵ
                        while (0 != KeyOnOutput)
                        {
                            __tk_scan();
                            KeyOnOutput = __tk_key_flag;
                        }

                        // send_status_keyval(KEY_PRESS_DOUBLECLICK, KEY_TK6);
                        return;
                    }
                }

                // �������ͬһ���������»���û��ֵ��˵���Ƕ̰�
                // send_status_keyval(KEY_PRESS_SHORT, KEY_TK6); // ���ʹ���״̬�ļ�ֵ
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
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK1);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK1);
                }
            }
        }
        else if (TK_CH3_VALIB == KeyOnOutput)
        {
            // ���KEY2������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK2);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK2);
                }
            }

            // display_data ^= 0x0200; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
        else if (TK_CH2_VALIB == KeyOnOutput)
        {
            // ���KEY3������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0400; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK3);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK3);
                }
            }

            // display_data ^= 0x0400; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
        else if (TK_CH0_VALIB == KeyOnOutput)
        {
            // ���KEY4������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK4);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK4);
                }
            }

            // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }
        else if (TK_CH9_VALIB == KeyOnOutput)
        {
            // ���KEY5������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK5);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK5);
                }
            }

            // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
            // led_display();          // LED״̬������ʾ
        }

        else if (TK_CH10_VALIB == KeyOnOutput)
        {
            // ���KEY6������
            if (cnt >= TK_LONG_KEY_TIME && cnt < 90)
            {
                // display_data ^= 0x0800; // ��Ӧ��LED״̬ȡ������������led_display()ˢ��
                // led_display();          // LED״̬������ʾ
                // send_status_keyval(KEY_PRESS_LONG, KEY_TK6);
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
                    // send_status_keyval(KEY_PRESS_CONTINUE, KEY_TK6);
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
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK1);
            break;

        case TK_CH3_VALIB:
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK2);
            break;

        case TK_CH2_VALIB:
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK3);
            break;

        case TK_CH0_VALIB:
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK4);
            break;

        case TK_CH9_VALIB:
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK5);
            break;

        case TK_CH10_VALIB:
            // send_status_keyval(KEY_PRESS_LOOSE, KEY_TK6);
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
