// ��ʱ��TMR2������ͷ�ļ�
#ifndef __TMR3_H
#define __TMR3_H

#include "include.h" // ʹ��оƬ�ٷ��ṩ��ͷ�ļ�

extern volatile u32 tmr3_cnt; // ��ʱ��TMR3�ļ���ֵ��ÿ�����жϷ������л��һ��

// ��ʱ��TMR3�ĳ�ʼ������ʼ����ɺ�Ĭ���ǹرյģ�
void tmr3_config(void);

// ������ʱ��TMR3����ʼ��ʱ
void tmr3_enable(void);

// �رն�ʱ������ռ���ֵ
void tmr3_disable(void);

#endif
