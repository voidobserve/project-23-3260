// my_config.h -- �Զ���������ļ�
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h" // ʹ��оƬ�ٷ��ṩ��ͷ�ļ�


// ============================================================
// �����Ҫ�޸�ʹ�õĴ�������������λ�ã���Ҫȥtk_config.h���޸�
// ����tk_user.c�����/�޸Ķ�Ӧ�Ĺ���
// ����������������ͨ��λ�ñ���Ҫһһ��Ӧ
// ============================================================

#define USE_MY_DEBUG 0
#include <stdio.h>

// ��������ʹ��P11��Ϊ���ͼ�ֵ�źŵ�����
// Ŀ���·����ʹ�õ���P21
// �����Ҫ�޸ģ�Ҫȥsend_key.c���޸�������صĳ�ʼ�����ú���
#define SEND_KEY_VAL_PIN            P11 // ���ͼ�ֵ�źŵ�����

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))


#include "tmr0.h" // ��⴮�ڽ��ճ�ʱ�Ķ�ʱ��
#include "uart0.h" // �����õĴ���
#include "uart1.h" // ����ָ��Ĵ���
#include "aip650.h" 
#include "send_key.h"

#endif // end file
