// ��ң���������ļ�ֵת����Ψһ�Ĺ���ֵ��Դ�ļ�
#include "key_conversion.h"
// #include "rf_learn.h"

// ����������ַ�ͼ�ֵ��ת���ɼ�ֵ��Ӧ�Ĺ���ֵ
// u8 key_to_funval(u16 addr, u8 key)
// {
//     u8 funval = 0x00;
//     u8 remote_type = 0x55; // ���ң�������͵ı���

//     u8 i = 0;
//     for (i = 0; i < ADDR_MAX_NUM; i++) // ���ݵ�ַ���ҵ����Ӧ��ң��������
//     {
//         if (addr_info.addr_buf[i] == addr)
//         {
//             remote_type = addr_info.remote_type[i];
//             break;
//         }
//     }

//     if (REMOTE_TYPE_SMALL_RM == remote_type)
//     {
//         // �����Сң����
//         // �������ļ�ֵ����ת��
//         switch (key)
//         {
//         case KEY_SMALL_RM_1: // ����--��
//             funval = KEY_FUNCTION_UP;
//             break;
//         case KEY_SMALL_RM_2: // ����--��
//             funval = KEY_FUNCTION_LEFT;
//             break;
//         case KEY_SMALL_RM_3: // ����--��Դ
//             funval = KEY_FUNCTION_POWER;
//             break;
//         case KEY_SMALL_RM_4: // ����--��
//             funval = KEY_FUNCTION_RIGHT;
//             break;
//         case KEY_SMALL_RM_5: // ����--��
//             funval = KEY_FUNCTION_DOWN;
//             break;
//         case KEY_SMALL_RM_6: // ����--�ƹ⡢����
//             funval = KEY_FUNCTION_LIGHT;
//             break;
//         case KEY_SMALL_RM_7: // ����--���֣���ť���Ǹ�����ͼ��
//             funval = KEY_FUNCTION_MUSIC_ICON;
//             break;
//         case KEY_SMALL_RM_8: // ����--�Զ�
//             funval = KEY_FUNCTION_AUTO;
//             break;
//         case KEY_SMALL_RM_9: // ����--�б�
//             funval = KEY_FUNCTION_LIST;
//             break;
//         case KEY_SMALL_RM_10: // ����--RAINBOW����ť�Ͼ����������
//             funval = KEY_FUNCTION_RAINBOW;
//             break;
//         }
//     }
//     else if (REMOTE_TYPE_BIG_RM == remote_type)
//     {
//         switch (key)
//         {
//         case KEY_BIG_RM_1: // ����--��Դ
//             funval = KEY_FUNCTION_POWER;
//             break;
//         case KEY_BIG_RM_2: // ����--����
//             funval = KEY_FUNCTION_MUTE;
//             break;
//         case KEY_BIG_RM_3: // ����--��
//             funval = KEY_FUNCTION_UP;
//             break;
//         case KEY_BIG_RM_4: // ����--��
//             funval = KEY_FUNCTION_LEFT;
//             break;
//         case KEY_BIG_RM_5: // ����--������ͣ
//             funval = KEY_FUNCTION_PLAY_PAUSE;
//             break;
//         case KEY_BIG_RM_6: // ����--��
//             funval = KEY_FUNCTION_RIGHT;
//             break;
//         case KEY_BIG_RM_7: // ����--��
//             funval = KEY_FUNCTION_DOWN;
//             break;
//         case KEY_BIG_RM_8: // ����--���֣���ť���Ǹ�MUSIC����
//             funval = KEY_FUNCTION_MUSIC_FONT;
//             break;
//         case KEY_BIG_RM_9: // ����--ģʽ
//             funval = KEY_FUNCTION_MODE;
//             break;
//         case KEY_BIG_RM_10: // ����--Ӱ�ӣ���ť����MOVIE����
//             funval = KEY_FUNCTION_MOVIE;
//             break;
//         case KEY_BIG_RM_11: // ����--TREB+������+
//             funval = KEY_FUNCTION_TREB_ADD;
//             break;
//         case KEY_BIG_RM_12: // ����--���ţ�NEWS
//             funval = KEY_FUNCTION_NEWS;
//             break;
//         case KEY_BIG_RM_13: // ����--����+��BASS+
//             funval = KEY_FUNCTION_BASS_ADD;
//             break;
//         case KEY_BIG_RM_14: // ����--����-��TREB-
//             funval = KEY_FUNCTION_TREB_SUB;
//             break;
//         case KEY_BIG_RM_15: // ����--��ʾ��DISPLAY
//             funval = KEY_FUNCTION_DISPLAY;
//             break;
//         case KEY_BIG_RM_16: // ����--����-��BASS--
//             funval = KEY_FUNCTION_BASS_SUB;
//             break;
//         }
//     }

//     return funval;
// }
