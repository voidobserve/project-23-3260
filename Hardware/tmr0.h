#ifndef __TMR0_H
#define __TMR0_H

#include "include.h" // ʹ��оƬ�ٷ��ṩ��ͷ�ļ�

#include "my_config.h" // �����Զ����ͷ�ļ�

// extern volatile bit tmr0_flag; // tmr0�жϷ������л���λ�ı�־λ
extern volatile u32 tmr0_cnt;            // ��ʱ��TMR0�ļ���ֵ��ÿ�����жϷ������л��һ��

void tmr0_config(void);
void tmr0_enable(void);
void tmr0_disable(void);


#endif
