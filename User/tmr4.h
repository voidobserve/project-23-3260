#ifndef __TMR4_H
#define __TMR4_H

#include "include.h" // ʹ��оƬ�ٷ��ṩ��ͷ�ļ�

extern volatile u32 tmr4_cnt; // ��ʱ��TMR4�ļ���ֵ��ÿ�����жϷ������л��һ��

void tmr4_config(void);  // ��ʱ��TMR4�ĳ�ʼ������ʼ����ɺ�Ĭ���ǹرյģ�
void tmr4_enable(void);  // ������ʱ��TMR4����ʼ��ʱ
void tmr4_disable(void); // �رն�ʱ������ռ���ֵ

#endif
