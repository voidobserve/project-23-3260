// ���ڷ��ͼ�ֵ��Դ����ʹ�õ��˶�ʱ��TMR1
#include "send_key.h"
#include "tmr2.h" // ��ʱ��TMR2�����ڷ��͸�ʽͷ����ʱ��ÿ�η��ͼ������ʱ

volatile char send_keyval_flag = 0; // �Ƿ�Ҫ���ͼ�ֵ�ı�־λ��0--�����ͣ�1--����

static volatile unsigned short key_val = 0; // Ҫ���͵�16λ���ݣ���λ����MSB

// ���ͼ�ֵ�ź����ŵĳ�ʼ������
// ���ŵ�Ĭ��״̬Ϊ�͵�ƽ
void send_keyval_pin_init(void)
{
#ifdef DEVELOPMENT_BOARD

    P1_MD0 &= ~(GPIO_P11_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P1_MD0 |= GPIO_P11_MODE_SEL(0x1);    // P1_1����Ϊ���ģʽ

    P1_PU |= GPIO_P11_PULL_UP(0x01); // �ڲ�����������

    FOUT_S11 = GPIO_FOUT_AF_FUNC; // ѡ��AF������������ֲ��������ָ��ù��������������߼��ߵ͵�ƽ�õģ�

    // λ��������p1_1����ߵ�ƽ��Ĭ�������Ŵ��ڿ���״̬������״̬Ϊ�ߵ�ƽ��
    P11 = 1;

#endif // end of #ifdef DEVELOPMENT_BOARD

#ifdef CIRCUIT_BOARD

    P3_MD0 &= ~(GPIO_P31_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P3_MD0 |=   GPIO_P31_MODE_SEL(0x1);    // P2_1����Ϊ���ģʽ
 
    P3_PU |= GPIO_P31_PULL_UP(0x01); // �ڲ�����������

    FOUT_S31 = GPIO_FOUT_AF_FUNC; // ѡ��AF������������ֲ��������ָ��ù��������������߼��ߵ͵�ƽ�õģ�

    // λ��������p2_1����ߵ�ƽ��Ĭ�������Ŵ��ڿ���״̬������״̬Ϊ�ߵ�ƽ��
    P31 = 1;

#endif // end of #ifdef CIRCUIT_BOARD
}

// ���ͼ�ֵ�źŵ�����ʹ�õĶ�ʱ���ĳ�ʼ��
// ����ʹ��TMR1��Ĭ�Ͻ����жϣ���Ҫʱ�ٿ���
void send_keyval_timer_init(void)
{
    // ���ö�ʱ�����������������ֵ���������
    __SetIRQnIP(TMR1_IRQn, TMR1_IQn_CFG); // �����ж����ȼ���TMR1��

    TMR1_CONL &= ~TMR_PRESCALE_SEL(0x03); // ���TMR1��Ԥ��Ƶ���üĴ���
    TMR1_CONL |= TMR_PRESCALE_SEL(0x05);  // ����TMR1��Ԥ��Ƶ��Ϊ16��Ƶ����21MHz / 32 = 0.65625MHz��Լ0.65625us����һ��
    TMR1_CONL &= ~TMR_MODE_SEL(0x03);     // ���TMR1��ģʽ���üĴ���
    TMR1_CONL |= TMR_MODE_SEL(0x01);      // ����TMR1��ģʽΪ������ģʽ������HIRC��������м���

    TMR1_CONH &= ~TMR_PRD_PND(0x01); // ���TMR1�ļ�����־λ����ʾδ��ɼ���
    TMR1_CONH |= TMR_PRD_IRQ_EN(1);  // ʹ��TMR1�ļ����ж�

    // ����TMR1�ļ�������
    TMR1_PRL = TMR1_CNT_TIME % 255;
    TMR1_PRH = TMR1_CNT_TIME / 255;

    // ���TMR1�ļ���ֵ
    TMR1_CNTL = 0;
    TMR1_CNTH = 0;

    TMR1_CONL &= ~(TMR_SOURCE_SEL(0x07)); // ���TMR1��ʱ��Դ���üĴ���
    // TMR1_CONL |= TMR_SOURCE_SEL(0x07); // ����TMR1��ʱ��Դ��ʹ��ϵͳʱ��
    TMR1_CONL |= TMR_SOURCE_SEL(0x05); // ����TMR1��ʱ��Դ�������κ�ʱ��
                                       // __EnableIRQ(TMR1_IRQn);			   // ʹ���ж�

    __DisableIRQ(TMR1_IRQn); // �����ж�
    // __EnableIRQ(TMR1_IRQn);
    // IE_EA = 1; // ʹ�����ж�
}

// ������ʱ��TMR1����ʼ��ʱ
void tmr1_enable(void)
{
    // ���¸�TMR1����ʱ��
    TMR1_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR1_CONL |= TMR_SOURCE_SEL(0x06);    // ���ö�ʱ����ʱ��Դ��ʹ��ϵͳʱ��

    __EnableIRQ(TMR1_IRQn); // ʹ���ж�
}

// �رն�ʱ��1����ռ���ֵ
void tmr1_disable(void)
{
    // ������ʱ���ṩʱ�ӣ�����ֹͣ����
    TMR1_CONL &= ~(TMR_SOURCE_SEL(0x07)); // �����ʱ����ʱ��Դ���üĴ���
    TMR1_CONL |= TMR_SOURCE_SEL(0x05);    // ���ö�ʱ����ʱ��Դ�������κ�ʱ��

    // �����ʱ���ļ���ֵ
    TMR1_CNTL = 0;
    TMR1_CNTH = 0;

    __DisableIRQ(TMR1_IRQn); // �ر��жϣ���ʹ���жϣ�
}

// ��ʱ��TMR1�жϷ�����
void TIMR1_IRQHandler(void) interrupt TMR1_IRQn
{
    // ÿ��Ҫ���͵Ķ����������ö�ʱ�������жϵ��ĸ�����������
    // ������3�����ڵĸߵ�ƽ+1�����ڵĵ͵�ƽ��ʾ"1"
    // ��1�����ڵĸߵ�ƽ+3�����ڵĵ͵�ƽ��ʾ"0"
    static volatile unsigned char cur_period = 0; // ��ǰ����

    static volatile unsigned char cur_bit = 0; // ��ǰҪ���͵ĵڼ�λ��������

    static volatile unsigned char last_period = 0; // ��־λ���Ƿ������һ��λ�����һ������

    // �����ж�����IP������ɾ��
    __IRQnIPnPush(TMR1_IRQn);

    // ---------------- �û��������� -------------------
    // �����ж�
    if (TMR1_CONH & TMR_PRD_PND(0x1))
    {
        TMR1_CONH |= TMR_PRD_PND(0x1); // ���pending

        // SEND_KEY_VAL_PIN = ~SEND_KEY_VAL_PIN; // �����ã��۲��ǲ����ܴ����жϣ��Լ�ÿ���жϴ�����ʱ����

        if (send_keyval_flag == 1)
        {
            // ���ͼ�ֵ

            // ���жϵ�ǰҪ���͵��ǵͼ�λ������������Ӧ���߼�ֵ�Ƕ���
            if (key_val & (0x01 << (15 - cur_bit)))
            {
                // �����ǰҪ���͵���"1"

                // �жϵ�ǰҪ���͵ڼ���������
                switch (cur_period)
                {
                case 0:
                    SEND_KEY_VAL_PIN = 1;
                    break;

                case 1:
                    SEND_KEY_VAL_PIN = 1;
                    break;

                case 2:
                    SEND_KEY_VAL_PIN = 1;
                    break;

                case 3:
                    SEND_KEY_VAL_PIN = 0;
                    break;
                }
            }
            else
            {
                // �����ǰҪ���͵���"0"

                // �жϵ�ǰҪ���͵ڼ���������
                switch (cur_period)
                {
                case 0:
                    SEND_KEY_VAL_PIN = 1;
                    break;

                case 1:
                    SEND_KEY_VAL_PIN = 0;
                    break;

                case 2:
                    SEND_KEY_VAL_PIN = 0;
                    break;

                case 3:
                    SEND_KEY_VAL_PIN = 0;
                    break;
                }
            }

            // ������һ�����ں󣬶�Ӧ�ļ���ֵ��һ
            cur_period++;
            if (cur_period >= 4)
            {
                // ����������ڴ��ڵ���4�ˣ�˵����������1λ��������
                cur_bit++;

                cur_period = 0; // ����һλ���������ĵ�0�����ڿ�ʼ��׼����һ�η���
            }

            if (cur_bit >= 16 && 0 == last_period)
            {
                // ������͵��˵�15λ��0~15�����������ĵ��ĸ����ڣ���4�����ڻ�δ��ɣ�
                last_period = 1;
                cur_bit--;
                cur_period = 3;
            }
            else if (cur_bit >= 16 && 1 == last_period) // �����������16λ��������
            {
                // ��ռ���ֵ��׼����һ�η���
                cur_bit = 0;
                cur_period = 0;
                last_period = 0;

                send_keyval_flag = 0; // ��ն�Ӧ�ı�־λ��׼����һ�μ�ֵ�ķ���
                SEND_KEY_VAL_PIN = 1; // �����ֵ����������Ϊ����״̬����ǰ״̬���ָߵ�ƽ
            }
        }
    }

    // �˳��ж�����IP������ɾ��
    __IRQnIPnPop(TMR1_IRQn);
}

// ����һ�ΰ�����ֵ(�ܹ�16bit)
void send_keyval(unsigned short send_data)
{
    key_val = send_data; // ���Ҫ���͵ļ�ֵ����ʱ�����жϷ��������ȡkey_val�е�ֵ��Ȼ���ͳ�ȥ

    // �ȷ���Э��ͷ�����ſ���״̬�Ǹߵ�ƽ���õ͵�ƽ��ΪЭ��ͷ��
    SEND_KEY_VAL_PIN = 0;

    // delay_ms(5);
    tmr2_enable();       // �򿪶�ʱ��TMR2�����濪ʼ�ö�ʱ����ʵ����ʱ5ms
    while (tmr2_cnt < 1) // TMR2����5ms��ŻὫ�������ֵ��һ
    {
        WDT_KEY = WDT_KEY_VAL(0xAA); // ι��
    }
    tmr2_disable(); // �رն�ʱ��TMR2�������ڲ������Ӳ���ļ���ֵ����
    tmr2_flag = 0;  // �����־λ
    tmr2_cnt = 0;   // tmr2_cnt = 0; // �����ʱ���ļ���ֵ

    tmr1_enable(); // �򿪶�ʱ�������ͼ�ֵ����
    send_keyval_flag = 1;
    while (send_keyval_flag != 0) // �ȴ��������
        ;
    tmr1_disable(); // �رն�ʱ��

    delay_ms(10); // ÿ����ֵ���ټ��10ms��Ҫ����5~10ms��

#if 0
    tmr2_enable();       // �򿪶�ʱ��TMR2������ͨ�����ö�ʱ����ʵ����ʱ10ms
    while (tmr2_cnt < 2) // TMR2����5ms��ŻὫ�������ֵ��һ
    {
        WDT_KEY = WDT_KEY_VAL(0xAA); // ι��
    }
    tmr2_disable(); // �رն�ʱ��TMR2�������ڲ������Ӳ���ļ���ֵ����
    tmr2_flag = 0;  // �����־λ
    tmr2_cnt = 0;   // tmr2_cnt = 0; // �����ʱ���ļ���ֵ
#endif
}

// ���ʹ��а���״̬��Ϣ��16λ����
// ǰ��λ��Ϣ��ʾ�̰��������������ͳ������ɿ�����ض�����rf_scan.h�У�
// ����λ��Ϣ��ʾ��ֵ
void send_status_keyval(u8 status, u8 key)
{
    u16 send_data = 0;

    // if (0 == key)
    // {
    //     return; // �����Ϳյļ�ֵ
    // }

    send_data = status << (5 + 8);  // ���̰���Ϣ��3bits��
    send_data |= (key & 0x1F) << 8; // ���5λ�ļ�ֵ
    send_data |= (~send_data >> 8); // ��8λ��ŷ���
    send_keyval(send_data);
}
