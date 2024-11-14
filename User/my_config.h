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

// ���ͼ�ֵ�źŵ�����
// �����Ҫ�޸ģ�Ҫȥsend_key.c���޸�������صĳ�ʼ�����ú���
#define SEND_KEY_VAL_PIN P11 // ���ͼ�ֵ�źŵ�����

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))

#define TOUCH_KEY_ID_1 TK_CH24_VALIB // ������ʶ--��������K1
#define TOUCH_KEY_ID_2 TK_CH25_VALIB // ������ʶ--��������K2
#define TOUCH_KEY_ID_3 TK_CH23_VALIB // ������ʶ--��������K3
#define TOUCH_KEY_ID_4 TK_CH17_VALIB // ������ʶ--��������K4
#define TOUCH_KEY_ID_5 TK_CH15_VALIB // ������ʶ--��������K5

#define DETECT_DOUBLE_CLICK_INTERVAL (100) // ���˫����ʱ����(��λ��ms)
#define LONG_PRESS_TIME_THRESHOLD_MS (750) // ����ʱ����ֵ����λ��ms��
#define HOLD_PRESS_TIME_THRESHOLD_MS (150) // ��������(������)��ʱ����ֵ(��λ��ms)��ÿ�� xx ʱ����Ϊ��һ�γ��������¼�
#define LOOSE_PRESS_CNT_MS (50)           // ���ּ�ʱ���ɿ��ֶ�ã�����Ϊ�����������
#define ONE_CYCLE_TIME_MS (0)              // ���������һ��ѭ�������ʱ�䣬��λ��ms (0--˵��ÿ�ε��øú�����ʱ��̣ܶ����Ժ��Բ���)

#include "tmr0.h"  // ��⴮�ڽ��ճ�ʱ�Ķ�ʱ��
#include "uart0.h" // �����õĴ���
#include "uart1.h" // ����ָ��Ĵ���
#include "aip650.h"
#include "send_key.h" // ���ͼ�ֵ����ؽӿڣ��ڲ�ʹ����tmr1��ʱ��

#endif // end file
