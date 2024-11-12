#include "tmr0.h"

// #define TMR0_CNT_TIME 152 // 152 * 0.65625us Լ����100us
// ��ʱ����ʱ���� (��λ:Hz)
// ����ֵ = ϵͳʱ�� / ��ʱ����Ƶ / Ƶ�� - 1
#define TMR0_PERIOD (SYSCLK / 128 / 1000 - 1) // 1000Hz,1ms

// volatile bit tmr0_flag = 0; // tmr0�жϷ������л���λ�ı�־λ
volatile u32 tmr0_cnt = 0; // ��ʱ��TMR0�ļ���ֵ��ÿ�����жϷ������л��һ��

/**
 * @brief ���ö�ʱ��TMR0
 */
void tmr0_config(void)
{
    __SetIRQnIP(TMR0_IRQn, TMR0_IQn_CFG); // �����ж����ȼ���TMR0��
    __DisableIRQ(TMR0_IRQn);              // ���ö�ʱ���ж�
    IE_EA = 1;                            // �����ж�

    // ���TMR0�ļ���ֵ
    TMR0_CNTL = 0;
    TMR0_CNTH = 0;

    TMR0_CONL &= ~TMR_PRESCALE_SEL(0x03); // ���TMR0��Ԥ��Ƶ���üĴ���
    TMR0_CONL |= TMR_PRESCALE_SEL(0x07); // ����Ԥ��Ƶ�Ĵ���,128��Ƶ
    TMR0_CONL &= ~TMR_MODE_SEL(0x03); // ���TMR0��ģʽ���üĴ���
    TMR0_CONL |= TMR_MODE_SEL(0x01);  // ����TMR0��ģʽΪ������ģʽ������ϵͳʱ�ӵ�������м���

    TMR0_CONH &= ~TMR_PRD_PND(0x01); // ���TMR0�ļ�����־λ����ʾδ��ɼ���
    TMR0_CONH |= TMR_PRD_IRQ_EN(1);  // ʹ��TMR0�ļ����ж�

    TMR0_PRH = TMR_PERIOD_VAL_H((TMR0_PERIOD >> 8) & 0xFF); // ����ֵ
    TMR0_PRL = TMR_PERIOD_VAL_L((TMR0_PERIOD >> 0) & 0xFF);

    TMR0_CONL &= ~(TMR_SOURCE_SEL(0x07)); // ���TMR0��ʱ��Դ���üĴ���
    TMR0_CONL |= TMR_SOURCE_SEL(0x05); // ����TMR0��ʱ��Դ�������κ�ʱ��
}

/**
 * @brief ������ʱ��TMR0����ʼ��ʱ
 */
void tmr0_enable(void)
{
    // ���¸�TMR0����ʱ��
    TMR0_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR0_CONL |= TMR_SOURCE_SEL(0x06);    // ���ö�ʱ����ʱ��Դ��ʹ��ϵͳʱ�ӣ�Լ21MHz��

    __EnableIRQ(TMR0_IRQn); // ʹ���ж�
    IE_EA = 1;              // �����ж�
}

/**
 * @brief �رն�ʱ��0����ռ���ֵ
 */
void tmr0_disable(void)
{
    // ������ʱ���ṩʱ�ӣ�����ֹͣ����
    TMR0_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR0_CONL |= TMR_SOURCE_SEL(0x05);    // ���ö�ʱ����ʱ��Դ�������κ�ʱ��

    // �����ʱ���ļ���ֵ
    TMR0_CNTL = 0;
    TMR0_CNTH = 0;

    __DisableIRQ(TMR0_IRQn); // �ر��жϣ���ʹ���жϣ�
}

// TMR0�жϷ�����
void TIMR0_IRQHandler(void) interrupt TMR0_IRQn
{
    // �����ж�����IP������ɾ��
    __IRQnIPnPush(TMR0_IRQn);

    // ---------------- �û��������� -------------------

    // �����ж�
    if (TMR0_CONH & TMR_PRD_PND(0x1))
    {
        TMR0_CONH |= TMR_PRD_PND(0x1); // ���pending

        tmr0_cnt++;

        // P11 = ~P11; // �����ã������жϴ��������Ƿ���ȷ

#if 0
        // �������5s
        if (TMR0_cnt == 1000)
        {
            TMR0_cnt = 0;
            TMR0_flag = 1; // ����Ӧ�ı�־λ��һ
        }
#endif
    }

    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(TMR0_IRQn);
}