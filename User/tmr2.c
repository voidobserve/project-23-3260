// ��ʱ��TMR2������Դ�ļ�
#include "tmr2.h"

volatile unsigned char tmr2_flag = 0; // tmr2�жϷ������л���λ�ı�־λ
volatile u32 tmr2_cnt = 0; // ��ʱ��TMR2�ļ���ֵ��ÿ�����жϷ������л��һ��

/**
 * @brief ���ö�ʱ��TMR2
 */
void tmr2_config(void)
{
    // ���ö�ʱ����������¼RF���յ��ĸߵ�ƽ����ʱ��
    __SetIRQnIP(TMR2_IRQn, TMR2_IQn_CFG); // �����ж����ȼ���TMR2��

    TMR2_CONL &= ~TMR_PRESCALE_SEL(0x03); // ���TMR2��Ԥ��Ƶ���üĴ���
    // ����TMR2��Ԥ��Ƶ��Ϊ32��Ƶ����21MHz / 32 = 0.67MHz��Լ0.67us����һ��
    // ��ʵ�ʲ��Ժͼ���ó����ϵͳʱ����21MHz�ģ����ǻ�����Щ������׼ȷ��21MHz��
    TMR2_CONL |= TMR_PRESCALE_SEL(0x05);
    TMR2_CONL &= ~TMR_MODE_SEL(0x03); // ���TMR2��ģʽ���üĴ���
    TMR2_CONL |= TMR_MODE_SEL(0x01);  // ����TMR2��ģʽΪ������ģʽ������ϵͳʱ�ӵ�������м���

    TMR2_CONH &= ~TMR_PRD_PND(0x01); // ���TMR2�ļ�����־λ����ʾδ��ɼ���
    TMR2_CONH |= TMR_PRD_IRQ_EN(1);  // ʹ��TMR2�ļ����ж�

    // ����TMR2�ļ�������
    TMR2_PRL = (unsigned char)(TMR2_CNT_TIME % 255);
    TMR2_PRH = (unsigned char)(TMR2_CNT_TIME / 255);

    // ���TMR2�ļ���ֵ
    TMR2_CNTL = 0;
    TMR2_CNTH = 0;

    TMR2_CONL &= ~(TMR_SOURCE_SEL(0x07)); // ���TMR2��ʱ��Դ���üĴ���
    // TMR2_CONL |= TMR_SOURCE_SEL(0x07); // ����TMR2��ʱ��Դ��ʹ��ϵͳʱ��
    TMR2_CONL |= TMR_SOURCE_SEL(0x05); // ����TMR2��ʱ��Դ�������κ�ʱ��
                                       // __EnableIRQ(TMR2_IRQn);			   // ʹ���ж�

    __DisableIRQ(TMR2_IRQn); // �����ж�
}

/**
 * @brief ������ʱ��TMR2����ʼ��ʱ
 */
void tmr2_enable(void)
{
    // ���¸�TMR2����ʱ��
    TMR2_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR2_CONL |= TMR_SOURCE_SEL(0x06);    // ���ö�ʱ����ʱ��Դ��ʹ��ϵͳʱ�ӣ�Լ21MHz��

    __EnableIRQ(TMR2_IRQn); // ʹ���ж�
}

/**
 * @brief �رն�ʱ��2����ռ���ֵ
 */
void tmr2_disable(void)
{
    // ������ʱ���ṩʱ�ӣ�����ֹͣ����
    TMR2_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR2_CONL |= TMR_SOURCE_SEL(0x05);    // ���ö�ʱ����ʱ��Դ�������κ�ʱ��

    // �����ʱ���ļ���ֵ
    TMR2_CNTL = 0;
    TMR2_CNTH = 0;

    __DisableIRQ(TMR2_IRQn); // �ر��жϣ���ʹ���жϣ�
}

// TMR2�жϷ�����
void TIMR2_IRQHandler(void) interrupt TMR2_IRQn
{
    // �����ж�����IP������ɾ��
    __IRQnIPnPush(TMR2_IRQn);

    // ---------------- �û��������� -------------------

    // �����ж�
    if (TMR2_CONH & TMR_PRD_PND(0x1))
    {
        TMR2_CONH |= TMR_PRD_PND(0x1); // ���pending

        tmr2_cnt++; // ÿ5ms��һ��

        // P12 = ~P12; // �����ã������жϴ��������Ƿ���ȷ

        // �������5s
        if (tmr2_cnt == 1000)
        {
            tmr2_cnt = 0;
            tmr2_flag = 1; // ����Ӧ�ı�־λ��һ
        }
    }

    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(TMR2_IRQn);
}
