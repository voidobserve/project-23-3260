/**
 ******************************************************************************
 * @file    User/tk_lib.c
 * @author  HUGE-IC Application Team
 * @version V1.0.0
 * @date    05-20-2022
 * @brief   Main program body
 ******************************************************************************
 * @attention
 * tk_set.c�ļ���ϵͳʹ�õ��ļ����������޸ġ�
 * ���º����ͱ����û�����Ҫ�޸�
 *
 *
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
/**
 * @}
 */
// ����һ��10ms���ж�
#define PEROID_VAL (SYSCLK / 128 / 100 - 1)
// �û��������޸�
volatile unsigned short xdata __tk_ch_data_0[TK_CH_USE] _at_(0x6000 + 0);
volatile unsigned short xdata __tk_ch_data_1[TK_CH_USE] _at_(0x6000 + TK_CH_USE * 2);
volatile unsigned short xdata __tk_ch_data_2[TK_CH_USE] _at_(0x6000 + TK_CH_USE * 4);
volatile unsigned short xdata __tk_ch_data_3[TK_CH_USE] _at_(0x6000 + TK_CH_USE * 8);
volatile unsigned short xdata __tk_ch_data_4[TK_CH_USE] _at_(0x6000 + TK_CH_USE * 10);
volatile unsigned short xdata __tk_ch_data_5[TK_CH_USE];
volatile unsigned short xdata __tk_ch_data_6[TK_CH_USE];
volatile unsigned short xdata __tk_ch_fth[TK_CH_USE];
volatile unsigned short xdata __tk_i_set[TK_CH_USE];
volatile unsigned char xdata __tk_update_cnt[TK_CH_USE];
volatile unsigned char xdata __tk_confirm_cnt[TK_CH_USE];
volatile unsigned char xdata __tk_leave_cnt[TK_CH_USE];
volatile unsigned char xdata __tk_ch_index[TK_CH_USE];

// �û��������޸�
unsigned long code __tk_adjust_line = TK_DATA_LINE;
unsigned short code __tk_adjust_time = TK_ADJUST_TIME;
unsigned short code __tk_adjust_diff_valu = TK_MAX_DIFF_VALU;
unsigned char code __tk_adjust_en = TK_ADJUST_EN;

unsigned short code __tk_valid_time = TK_VALID_TIME;
unsigned short code __tk_long_key_time = TK_LONG_KEY_TIME;
unsigned short code __tk_noise_value = TK_NOISE_VAL;
unsigned char code __tk_cs_en = TK_CS_EN;
unsigned char code __tk_tp_en = TK_TP_EN;
unsigned char code __tk_nm_num = TK_MU_CNT;
unsigned char code __tk_base_update_cnt = TK_UPDATE_CNT;
unsigned char code __tk_nm_cm_value = TK_NM_CM_CNT;
unsigned char code __tk_cm_valu = TK_CM_VALE;
unsigned char code __tk_use_num = TK_CH_USE;

/*
**����ͨ����Ϣ��
*/
static u16 code TK_CH_EN_BUG[][2] =
    {
#if TK0_CH_EN
        {
            0u,           // ͨ��ֵ
            TK0_THR_DATA, // ����ֵ
        },
#endif

#if TK1_CH_EN
        {
            1u,
            TK1_THR_DATA,
        },
#endif

#if TK2_CH_EN
        {
            2u,
            TK2_THR_DATA,
        },
#endif

#if TK3_CH_EN
        {
            3u,
            TK3_THR_DATA,
        },
#endif

#if TK4_CH_EN
        {
            4u,
            TK4_THR_DATA,
        },
#endif

#if TK5_CH_EN
        {
            5u,
            TK5_THR_DATA,
        },
#endif

#if TK6_CH_EN
        {
            6u,
            TK6_THR_DATA,
        },
#endif

#if TK7_CH_EN
        {
            7u,
            TK7_THR_DATA,
        },
#endif

#if TK8_CH_EN
        {
            8u,
            TK8_THR_DATA,
        },
#endif

#if TK9_CH_EN
        {
            9u,
            TK9_THR_DATA,
        },
#endif

#if TK10_CH_EN
        {
            10u,
            TK10_THR_DATA,
        },
#endif

#if TK11_CH_EN
        {
            11u,
            TK11_THR_DATA,
        },
#endif

#if TK12_CH_EN
        {
            12u,
            TK12_THR_DATA,
        },
#endif

#if TK13_CH_EN
        {
            13u,
            TK13_THR_DATA,
        },
#endif

#if TK14_CH_EN
        {
            14u,
            TK14_THR_DATA,
        },
#endif

#if TK15_CH_EN
        {
            15u,
            TK15_THR_DATA,
        },
#endif

#if TK16_CH_EN
        {
            16u,
            TK16_THR_DATA,
        },
#endif

#if TK17_CH_EN
        {
            17u,
            TK17_THR_DATA,
        },
#endif

#if TK18_CH_EN
        {
            18u,
            TK18_THR_DATA,
        },
#endif

#if TK19_CH_EN
        {
            19u,
            TK19_THR_DATA,
        },
#endif

#if TK20_CH_EN
        {
            20u,
            TK20_THR_DATA,
        },
#endif

#if TK21_CH_EN
        {
            21u,
            TK21_THR_DATA,
        },
#endif

#if TK22_CH_EN
        {
            22u,
            TK22_THR_DATA,
        },
#endif

#if TK23_CH_EN
        {
            23u,
            TK23_THR_DATA,
        },
#endif

#if TK24_CH_EN
        {
            24u,
            TK24_THR_DATA,
        },
#endif

#if TK25_CH_EN
        {
            25u,
            TK25_THR_DATA,
        },
#endif
};

/**
 * @brief  Touchkey gpio init function
 * @param  None
 * @retval None
 */
void tk_gpio_config(void)
{
    u8 i = 0;

    for (i = 0; i < TK_CH_USE; i++)
    {

        if (__tk_ch_index[i] < 8)
        {
            if (__tk_ch_index[i] < 4)
            {
                P0_MD0 &= ~(0x3 << (__tk_ch_index[i] - 0) * 2);
                P0_MD0 |= (0x3 << (__tk_ch_index[i] - 0) * 2);
            }
            else
            {
                P0_MD1 &= ~(0x3 << (__tk_ch_index[i] - 4) * 2);
                P0_MD1 |= (0x3 << (__tk_ch_index[i] - 4) * 2);
            }
        }
        else if ((__tk_ch_index[i] >= 8) && (__tk_ch_index[i] < 16))
        {
            if (__tk_ch_index[i] < 12)
            {
                P1_MD0 &= ~(0x3 << (__tk_ch_index[i] - 8) * 2);
                P1_MD0 |= (0x3 << (__tk_ch_index[i] - 8) * 2);
            }
            else
            {
                P1_MD1 &= ~(0x3 << (__tk_ch_index[i] - 12) * 2);
                P1_MD1 |= (0x3 << (__tk_ch_index[i] - 12) * 2);
            }
        }
        else
        {
            if (__tk_ch_index[i] < 20)
            {
                P2_MD0 &= ~(0x3 << (__tk_ch_index[i] - 16) * 2);
                P2_MD0 |= (0x3 << (__tk_ch_index[i] - 16) * 2);
            }
            else
            {
                P2_MD1 &= ~(0x3 << (__tk_ch_index[i] - 20) * 2);
                P2_MD1 |= (0x3 << (__tk_ch_index[i] - 20) * 2);
            }
        }
    }
}

/**
 * @brief  Touchkey_IRQHandler
 * @param  none
 * @retval None
 */
void TK_IRQHandler(void) interrupt TK_IRQn
{
    __IRQnIPnPush(TK_IRQn);
    if (TK_CON2 & (0x1 << 6))
    {
        TK_CON2 |= (0x1 << 6);
        __tk_handler();
    }
    __IRQnIPnPop(TK_IRQn);
}

/**
 * @brief  Touchkey Module init function
 * @param  None
 * @retval None
 */
void tk_init(void)
{
    IE_EA = 1;
    IE3 |= (0x1 << 3);
    IP6 |= (0x3 << 6);
    CLK_CON2 |= (0x1 << 6);
    __EnableIRQ(TK_IRQn);
    TK_ACON0 = 0x3F;
    TK_ACON1 = 0x4B;
    TK_ACON3 = 0x30;
    TK_PSRCNT = 0x2F;
    TK_APRECHARGE = 0x4f;
    TK_APREDISCH = 0x27;
    TK_ACONVTIME = 0xA8;
    TK_BASEDIV0 = 0x10;
    TK_BASEDIV1 = 0x0;
    TK_BASEDIV2 = 0x0;
    TK_BASEDIV3 = 0x0;
    TK_CHCON3 = 0xD0;
    TK_CON0 = 0x4;
    TK_CON1 = 0x1E;
    TK_CON2 = 0x02;
}

/**
 * @brief  TIMR0_IRQHandler function
 * @param  None
 * @retval None
 */
void WUT_IRQHandler(void) interrupt WUT_IRQn
{
    // �����ж�����IP������ɾ��
    __IRQnIPnPush(WUT_IRQn);
    // �����ж�
    if (WUT_CONH & TMR_PRD_PND(0x1))
    {
        WUT_CONH |= TMR_PRD_PND(0x1); // ���pending
        __tk_ms_handler();            // ��Դ�ģ���֪������ʲô������ȥ����CPU����˯�ߣ���λΪms���ֲ���˵��˯��300ms��
    }

    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(WUT_IRQn);
}

#if 0
/**
 * @brief  TIMER Module init function
 * @param  None
 * @retval None
 */
void wut_init(void)
{
    __EnableIRQ(WUT_IRQn);
    IE_EA = 1;

    // ����timer2�ļ������ܣ�����һ��10ms���ж�
    TMR_ALLCON = WUT_CNT_CLR(0x1);
    WUT_PRH = TMR_PERIOD_VAL_H((PEROID_VAL >> 8) & 0xFF);                       // timer2�������ڸ�8λ
    WUT_PRL = TMR_PERIOD_VAL_L((PEROID_VAL >> 0) & 0xFF);                       // timer2�������ڵ�8λ
    WUT_CONH = TMR_PRD_PND(0x1) | TMR_PRD_IRQ_EN(0x1);                          // ����жϱ�־λ��ʹ���ж�
    WUT_CONL = TMR_SOURCE_SEL(0x7) | TMR_PRESCALE_SEL(0x7) | TMR_MODE_SEL(0x1); // ����timer2ʱ��Դ��Ԥ��Ƶֵ��ģʽ
}
#endif // end void wut_init(void)

/**
 * @brief  Touchkey  parameter configuration function
 *         �����������ú���
 *
 * @param  None
 * @retval None
 */
void tk_param_init(void)
{
    u8 i = 0;

    /* ����ͨ���������������ȳ�ʼ�� */
    for (i = 0; i < TK_CH_USE; i++)
    {
        __tk_ch_index[i] = (u8)(TK_CH_EN_BUG[i][0] & 0xff); // ��Ű���ͨ����Ϣ
        __tk_ch_fth[i] = TK_CH_EN_BUG[i][1];                // ��Ű���ͨ����Ϣ
        __tk_i_set[i] = TK_CURR_GEAR;                       // ������
        __tk_ch_en |= (1UL << __tk_ch_index[i]);            // ����ͨ��ʹ��
    }

    /* ����IO���ú��� */
    tk_gpio_config();

    /* �⺯����ʼ�� */
    __tk_lib_init(); // �����˿⣨��Դ��

    /* ����ģ�����ú��� */
    tk_init();

    /* ��ʱ�����ú��� */
    // wut_init();
}

// /**
//  * @brief  Touchkey  Circular execution function
//  * @param  None
//  * @retval None
//  */
// void tk_handle(void)
// {
//     // u32 tmp = 0; // ��ʱ������������
// }

/*************************** (C) COPYRIGHT 2022 TAIXIN-IC ***** END OF FILE *****/
