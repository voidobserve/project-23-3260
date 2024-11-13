// ���ڷ��ͼ�ֵ��ͷ�ļ�
#ifndef __SEND_KEY_H
#define __SEND_KEY_H

#include "include.h" // ʹ��оƬ�ٷ��ṩ��ͷ�ļ�

#include "my_config.h"

#ifndef SEND_KEY_VAL_PIN
#define SEND_KEY_VAL_PIN        P11 // ���ͼ�ֵ�źŵ�����
#endif // end of #ifndef SEND_KEY_VAL_PIN

// ��ʱ��TMR1�Ķ�ʱ���ڣ�����Ϊÿ200us����һ���ж�
// ��ʵ���������п�����200us���п�����240us���п�����160us��200us�Ĵ������ܶ࣬
// ��Ϊ��������ǵ��Գ����ģ�һ��ʼ��ʵ�ʵļ����г��룬���Ժ�����õ��Եķ�����
// �ڶ�ʱ���жϷ������У�һλ���������ֳ��ĸ����������ͣ�һ�����ھ���200us����
// ����޸��޸����ڣ����Ե�������������ֵ
// #define TMR1_CNT_TIME           (1800 / 3)
#define TMR1_CNT_TIME           305 // 305 * 0.65625 us Լ���� 200 us

// �Զ��崥�������ļ�ֵ
enum
{
    TOUCH_KEY1 = 0x01,
    TOUCH_KEY2 = 0x02,
    TOUCH_KEY3 = 0x03,
    TOUCH_KEY4 = 0x04,
    TOUCH_KEY5 = 0x05,
};

// �������̰��ȶ���
enum
{
    KEY_PRESS_SHORT = 0x00,      // �����̰�
    KEY_PRESS_LONG = 0x01,       // ��������
    KEY_PRESS_CONTINUE = 0x02,   // ����
    KEY_PRESS_LOOSE = 0x03,      // �������ɿ�
    KEY_PRESS_DOUBLECLICK = 0x04, // ����˫��������������ң���������ģ�
};

extern volatile bit send_keyval_flag; // �Ƿ�Ҫ���ͼ�ֵ�ı�־λ��0--�����ͣ�1--����

void send_keyval_pin_init(void);   // ���ͼ�ֵ�����Ž��г�ʼ��
void send_keyval_timer_init(void); // ���ͼ�ֵ������Ҫ����ʹ�õ��Ķ�ʱ�����г�ʼ������ʱ����ʼ����Ϊ�ر�״̬

// void tmr1_enable(void);  // ������ʱ��TMR1
// void tmr1_disable(void); // �رն�ʱ��TMR1����ռ���ֵ

void send_keyval(unsigned short send_data); // ����һ�ΰ�����ֵ���ܹ�16bit��
void send_status_keyval(u8 status, u8 key); // ���ʹ��а���״̬��Ϣ��16λ����

#endif // end of file
