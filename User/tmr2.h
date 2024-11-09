// ��ʱ��TMR2������ͷ�ļ�
#ifndef __TMR2_H
#define __TMR2_H

#include "include.h" // ����оƬ�ٷ��ṩ��ͷ�ļ�

// ��ʱ��TMR2�ļ�ʱ���ڣ�Ҳ���жϴ������ڣ�ÿ����ô���һ���жϣ�
// ��ʱ���ڲ��ܴ���65535����ΪTMR2��ż�ʱ���ڵļĴ���ֻ��16λ
// �����ö�ʱ��TMR2ÿ5ms����һ���ж�
#define TMR2_CNT_TIME ((7619))           // 5000us / 0.65625us == 7462��������Եó���7500����ӽ�5ms

extern volatile unsigned char tmr2_flag; // tmr2�жϷ������л���λ�ı�־λ
extern volatile u32 tmr2_cnt; // ��ʱ��TMR2�ļ���ֵ��ÿ�����жϷ������л��һ��

void tmr2_config(void); // ��ʱ��tmr2�ĳ�ʼ��
void tmr2_enable(void); // ������ʱ��TMR2����ʼ��ʱ
void tmr2_disable(void); // �رն�ʱ��TMR2����ռ���ֵ

#endif
