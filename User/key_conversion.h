// ��ң���������ļ�ֵת����Ψһ�Ĺ���ֵ��ͷ�ļ�
#ifndef __KEY_CONVERSION_H
#define __KEY_CONVERSION_H

#include "include.h" // ����оƬ�ٷ��ṩ��ͷ�ļ�

// ��С��RF-433ң������������ַ
#define ADDR_SMALL_RM 0x2830

// �ϴ��RF-433ң������������ַ
#define ADDR_BIG_RM 0x2838

// �Զ���ļ�ֵ
// ʵ��Ҫʹ�õĴ��������ļ�ֵ
enum
{
    KEY_TK1 = 0x16, // KEY1��5λ��ֵ 0b 0001 0110
    KEY_TK2 = 0x17, // KEY2��5λ��ֵ 0b 0001 0111
    KEY_TK3 = 0x18, // KEY3��5λ��ֵ 0b 0001 1000
    KEY_TK4 = 0x19, // KEY4��5λ��ֵ 0b 0001 1001
    KEY_TK5 = 0x1A, // KEY5��5λ��ֵ 0x 0001 1010
    KEY_TK6 = 0x1B  // KEY6��5λ��ֵ 0x 0001 1011
};

// ��С��ң������Ӧ��ʵ�ʼ�ֵ
// ���������ҡ����ϵ���
enum
{
    KEY_SMALL_RM_1 = 0x01,
    KEY_SMALL_RM_2 = 0x02,
    KEY_SMALL_RM_3 = 0x03,
    KEY_SMALL_RM_4 = 0x04,
    KEY_SMALL_RM_5 = 0x05,
    KEY_SMALL_RM_6 = 0x06,
    KEY_SMALL_RM_7 = 0x07,
    KEY_SMALL_RM_8 = 0x08,
    KEY_SMALL_RM_9 = 0x09,
    KEY_SMALL_RM_10 = 0x0A
};

// �ϴ��ң������Ӧ��ʵ�ʼ�ֵ
// ���������ҡ����ϵ���
enum
{
    KEY_BIG_RM_1 = 0x01,
    KEY_BIG_RM_2 = 0x02,
    KEY_BIG_RM_3 = 0x03,
    KEY_BIG_RM_4 = 0x04,
    KEY_BIG_RM_5 = 0x05,
    KEY_BIG_RM_6 = 0x06,
    KEY_BIG_RM_7 = 0x07,
    KEY_BIG_RM_8 = 0x08,
    KEY_BIG_RM_9 = 0x09,
    KEY_BIG_RM_10 = 0x0A,

    KEY_BIG_RM_11 = 0x0B,
    KEY_BIG_RM_12 = 0x0C,
    KEY_BIG_RM_13 = 0x0D,
    KEY_BIG_RM_14 = 0x0E,
    KEY_BIG_RM_15 = 0x0F,
    KEY_BIG_RM_16 = 0x10
};

/*
    ת��֮��ÿ��������Ӧһ�����ܣ�����ÿ������ȷ��һ��Ψһ�ļ�ֵ��
    ��ͬ���ܵİ���������ͬ�ļ�ֵ
*/
enum
{
    KEY_FUNCTION_POWER = 0x01, // ��Դ����
    KEY_FUNCTION_UP = 0x02,    // ����--��
    KEY_FUNCTION_LEFT = 0x03,  // ����--��
    KEY_FUNCTION_RIGHT = 0x04, // ����--��
    KEY_FUNCTION_DOWN = 0x05,  // ����--��

    KEY_FUNCTION_LIGHT = 0x06,      // ����--����
    KEY_FUNCTION_MUSIC_ICON = 0x07, // ����--���֣��������Ǹ�����ͼ�꣩
    KEY_FUNCTION_AUTO = 0x08,       // ����--�Զ�
    KEY_FUNCTION_LIST = 0x09,       // ����--�б�
    KEY_FUNCTION_RAINBOW = 0x0A,    // ����--�ʺ磨���ֶ����ģ�

    KEY_FUNCTION_MUTE = 0x0B,       // ����--����
    KEY_FUNCTION_PLAY_PAUSE = 0x0C, // ����--������ͣ
    KEY_FUNCTION_MUSIC_FONT = 0x0D, // ����--���֣���ť�Ͼ���"MUSIC"������
    KEY_FUNCTION_MODE = 0x0E,       // ����--ģʽ
    KEY_FUNCTION_MOVIE = 0x0F,      // ����--Ӱ��

    KEY_FUNCTION_TREB_ADD = 0x10, // ����--����+
    KEY_FUNCTION_TREB_SUB = 0x13, // ����--����-

    KEY_FUNCTION_NEWS = 0x11,    // ����--����
    KEY_FUNCTION_DISPLAY = 0x14, // ����--��ʾ

    KEY_FUNCTION_BASS_ADD = 0x12, // ����--����+
    KEY_FUNCTION_BASS_SUB = 0x15  // ����--����-
};


// ����������ַ�ͼ�ֵ��ת���ɼ�ֵ��Ӧ�Ĺ���ֵ
u8 key_to_funval(u16 addr, u8 key);

#endif
