// ��ʱ��TMR3������Դ�ļ�
#include "tmr3.h"

// ��ʱ��TMR3�ļ�ʱ���ڣ�Ҳ���жϴ������ڣ�ÿ����ô���һ���жϣ�
// ��ʱ���ڲ��ܴ���65535����ΪTMR3��ż�ʱ���ڵļĴ���ֻ��16λ
// 0.65625 * 15238 Լ���� 10000������ʱ��ÿ 10000us��10ms�� ����һ���ж�
// ʵ���ϻ���Ҫ����������ʱ�Ӳ��Ǻ�׼ȷ����Ϊ���Ǿ����ṩ�ģ�����RC���ṩ��
#define TMR3_CNT_TIME ((15100)) 

volatile u32 tmr3_cnt = 0; // ��ʱ��TMR3�ļ���ֵ��ÿ�����жϷ������л��һ��

// ��ʱ��TMR3�ĳ�ʼ������ʼ����ɺ�Ĭ���ǹرյģ�
void tmr3_config(void)
{
    // ���ö�ʱ����������¼RF���յ��ĸߵ�ƽ����ʱ��
    __SetIRQnIP(TMR3_IRQn, TMR3_IQn_CFG); // �����ж����ȼ���TMR3��

    TMR3_CONL &= ~TMR_PRESCALE_SEL(0x03); // ���TMR3��Ԥ��Ƶ���üĴ���
    // ����TMR3��Ԥ��Ƶ��Ϊ32��Ƶ����21MHz / 32 = 0.65625MHz��Լ0.65625us����һ��
    // ��ʵ�ʲ��Ժͼ���ó����ϵͳʱ����21MHz�ģ����ǻ�����Щ��
    TMR3_CONL |= TMR_PRESCALE_SEL(0x05);
    TMR3_CONL &= ~TMR_MODE_SEL(0x03); // ���TMR3��ģʽ���üĴ���
    TMR3_CONL |= TMR_MODE_SEL(0x01);  // ����TMR3��ģʽΪ������ģʽ������ϵͳʱ�ӵ�������м���

    TMR3_CONH &= ~TMR_PRD_PND(0x01); // ���TMR3�ļ�����־λ����ʾδ��ɼ���
    TMR3_CONH |= TMR_PRD_IRQ_EN(1);  // ʹ��TMR3�ļ����ж�

    __DisableIRQ(TMR3_IRQn); // �����ж�

    // ����TMR3�ļ�������
    TMR3_PRL = (unsigned char)(TMR3_CNT_TIME % 255);
    TMR3_PRH = (unsigned char)(TMR3_CNT_TIME / 255);

    // ���TMR3�ļ���ֵ
    TMR3_CNTL = 0;
    TMR3_CNTH = 0;

    TMR3_CONL &= ~(TMR_SOURCE_SEL(0x07)); // ���TMR3��ʱ��Դ���üĴ���
    // TMR3_CONL |= TMR_SOURCE_SEL(0x07); // ����TMR3��ʱ��Դ��ʹ��ϵͳʱ��
    TMR3_CONL |= TMR_SOURCE_SEL(0x05); // ����TMR3��ʱ��Դ�������κ�ʱ��
                                       // __EnableIRQ(TMR3_IRQn);			   // ʹ���ж�
}

// ������ʱ��TMR3����ʼ��ʱ
void tmr3_enable(void)
{
    // ���¸�TMR3����ʱ��
    TMR3_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR3_CONL |= TMR_SOURCE_SEL(0x06);    // ���ö�ʱ����ʱ��Դ��ʹ��ϵͳʱ�ӣ�Լ21MHz��

    __EnableIRQ(TMR3_IRQn); // ʹ���ж�
}

// �رն�ʱ������ռ���ֵ
void tmr3_disable(void)
{
    // ������ʱ���ṩʱ�ӣ�����ֹͣ����
    TMR3_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR3_CONL |= TMR_SOURCE_SEL(0x05);    // ���ö�ʱ����ʱ��Դ�������κ�ʱ��

    // �����ʱ���ļ���ֵ
    TMR3_CNTL = 0;
    TMR3_CNTH = 0;

    __DisableIRQ(TMR3_IRQn); // �ر��жϣ���ʹ���жϣ�
}

// TMR3�жϷ�����
void TIMR3_IRQHandler(void) interrupt TMR3_IRQn
{
    // �����ж�����IP������ɾ��
    __IRQnIPnPush(TMR3_IRQn);

    // ---------------- �û��������� -------------------
    // �����ж�
    if (TMR3_CONH & TMR_PRD_PND(0x1))
    {
        TMR3_CONH |= TMR_PRD_PND(0x1); // ���pending

        tmr3_cnt++; // 

        // P12 = ~P12; // �����ã������жϴ��������Ƿ���ȷ
    }
    
    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(TMR3_IRQn);
}
