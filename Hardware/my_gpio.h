// GPIO���õ�ͷ�ļ�
#ifndef __MY_GPIO_H
#define __MY_GPIO_H

#include "include.h" // ����оƬ�ٷ��ṩ��ͷ�ļ�

// ����������LED�������ӵ�����
#define LED6        P01
#define LED7        P26

void p12_output_config(void); // P12����Ϊ���ģʽ


void p01_output_config(void); // P01���ӵ��˿������LED6������
void p26_output_config(void); // P26���ӵ��˿������LED7������P26����Ϊ���ģʽ

#endif
