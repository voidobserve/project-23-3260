#include "tmr4.h"

#define TMR4_CNT_TIME 1520 // 1520 * 0.65625us Լ����1000us��1ms

volatile u32 tmr4_cnt = 0; // ��ʱ��TMR4�ļ���ֵ��ÿ�����жϷ������л��һ��
// volatile bit tmr4_flag = 0; // tmr4�жϷ������л���λ�ı�־λ

// ��ʱ��TMR4�ĳ�ʼ������ʼ����ɺ�Ĭ���ǹرյģ�
void tmr4_config(void)
{
    __EnableIRQ(TMR4_IRQn);                                   // ��TIMER4ģ���ж�
    TMR_ALLCON = TMR4_CNT_CLR(0x1);                           // Timer4 ��������
    TMR4_CAP10 = TMR4_PRD_VAL_L((TMR4_CNT_TIME >> 0) & 0xFF); // ���ڵͰ�λ�Ĵ���
    TMR4_CAP11 = TMR4_PRD_VAL_H((TMR4_CNT_TIME >> 8) & 0xFF); // ���ڸ߰�λ�Ĵ���
    TMR4_CON0 = TMR4_PRESCALE_SEL(0x05) |                     // 32��Ƶ
                TMR4_SOURCE_SEL(0x7) |                        // ����Դѡ��ϵͳʱ��
                TMR4_MODE_SEL(0x0);                           // ����ģʽ
    TMR4_IE0 = TMR4_PRD_IRQ_EN(0x1);                          // ʹ�ܼ���ֵ��������ֵ�ж�
    TMR4_EN = TMR4_EN(0x0);                                   // ��ʹ�ܶ�ʱ��

    IE_EA = 1; // ʹ�����ж�
}

// ������ʱ��TMR4����ʼ��ʱ
void tmr4_enable(void)
{
    TMR4_EN = TMR4_EN(0x1); // ʹ�ܶ�ʱ��
}

// �رն�ʱ������ռ���ֵ
void tmr4_disable(void)
{
    TMR4_EN = TMR4_EN(0x0);         // ��ʹ�ܶ�ʱ��
    TMR_ALLCON = TMR4_CNT_CLR(0x1); // Timer4 ��������
}

// TMR4�жϷ�����
void TIMR4_IRQHandler(void) interrupt TMR4_IRQn
{
#if 1 // ��ʱ���Ķ�ʱ�ж�
    // �����ж�����IP������ɾ��
    __IRQnIPnPush(TMR4_IRQn);

    // ---------------- �û��������� -------------------
    // ����ֵ��������ֵ�ж�
    if (TMR4_FLAG0 & TMR4_PRD_FLAG(0x1))
    {
        TMR4_CLR0 |= TMR4_PRD_FLG_CLR(0x1);

        tmr4_cnt++;

        // P24 = ~P24; // �����ã������жϴ���ʱ���Ƿ�һ��
    }

    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(TMR4_IRQn);
#endif
}
