/**
  ***********************************************************************************************
  * @file    User/tk_config.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    05-20-2022
  * @brief   Main program body
  ***********************************************************************************************
  * @attention
  * ���������������ã�CS�������á����Թ��ܿ��ء�������ʱ�䡢�������������ȣ�
  * ����ϵͳ���ã�����ͨ��ʹ�ܡ�����ͨ�����������ã�
  * 
  * 
  ***********************************************************************************************
  */ 
#ifndef __TK_CONFIG_H
#define __TK_CONFIG_H
/* Includes ------------------------------------------------------------------------------------*/
#include "my_config.h"

/************************************************************************************************
******************************�û���������user configuration area********************************
*************************************************************************************************/
/* ���������������� *****************************************************************************/
#ifdef DEVELOPMENT_BOARD
#define TK_CS_EN                        ( 0 )                 // 1: ����CS����;  0: �ر�CS����
#define TK_TP_EN                        ( 0 )                 // 1: ����TP����;  0: �ر�TP����
#define TK_DEBUG_EN                     ( 0 )                 // 1: �������Թ���;  0: �رյ��Թ���
#define TK_MU_CNT                       ( 1 )                 // 1����1Ϊ��ˮģʽ������ֵ��ϼ�ģʽ
#define TK_UPDATE_CNT                   ( 15 )                // BASE ����ʱ��(��λ��10ms)
#define TK_LONG_KEY_TIME                ( 75 )                // ������ʱ��(��λ��10ms)
#define TK_VALID_TIME                   ( 500 )               // ������Чʱ��(��λ��10ms)
#define TK_NM_CM_CNT                    ( 4 )                 // ������������
#define TK_NOISE_VAL                    ( 10 )                // ��������ֵ
#define TK_CM_VALE                      ( 5 )                 // �����ͷų���
#define TK_CH_MAX                       ( 26 )                // ������󰴼�����
#define TK_CH_USE                       ( 4 )                 // ��Ҫʹ�õİ�������
#endif

#ifdef CIRCUIT_BOARD
#define TK_CS_EN                        ( 0 )                 // 1: ����CS����;  0: �ر�CS����
#define TK_TP_EN                        ( 0 )                 // 1: ����TP����;  0: �ر�TP����
#define TK_DEBUG_EN                     ( 0 )                 // 1: �������Թ���;  0: �رյ��Թ���
#define TK_MU_CNT                       ( 1 )                 // 1����1Ϊ��ˮģʽ������ֵ��ϼ�ģʽ
#define TK_UPDATE_CNT                   ( 15 )                // BASE ����ʱ��(��λ��10ms)
#define TK_LONG_KEY_TIME                ( 75 )                // ������ʱ��(��λ��10ms)
#define TK_VALID_TIME                   ( 500 )               // ������Чʱ��(��λ��10ms)
#define TK_NM_CM_CNT                    ( 4 )                 // ������������
#define TK_NOISE_VAL                    ( 10 )                // ��������ֵ
#define TK_CM_VALE                      ( 5 )                 // �����ͷų���
#define TK_CH_MAX                       ( 26 )                // ������󰴼�����
#define TK_CH_USE                       ( 6 )                 // ��Ҫʹ�õİ�������
#endif

// �Զ���ļ�ֵ
#if 0
// ʵ��Ҫʹ�õļ�ֵ
#define KEY_TK1 0x1B // KEY1��5λ��ֵ 0b 0001 1011
#define KEY_TK2 0x1C // KEY2��5λ��ֵ 0b 0001 1100
#define KEY_TK3 0x1D // KEY3��5λ��ֵ 0b 0001 1101
#define KEY_TK4 0x1E // KEY4��5λ��ֵ 0b 0001 1110
#define KEY_TK5 0x1F // KEY5��5λ��ֵ 0x 0001 1111
#define KEY_TK6 0x20 // KEY6��5λ��ֵ 0x 0010 0000
#endif


#if 0 // �����崥�������ļ�ֵ
// ����RF-433��ң���������һ�������ļ�ֵ��0b 0001 0000�������0b 0001 0001��ʼ
#define KEY_TK1 0x11 // �����尴��TK1��5λ��ֵ 0b 0001 0001
#define KEY_TK2 0x12 // �����尴��TK2��5λ��ֵ 0b 0001 0010
#define KEY_TK3 0x13 // �����尴��TK3��5λ��ֵ 0b 0001 0011
#define KEY_TK4 0x14 // �����尴��TK4��5λ��ֵ 0b 0001 0100

#define KEY_TK5 0x15 // TK5��5λ��ֵ 0x 0001 0101
#define KEY_TK6 0x16 // TK6��5λ��ֵ 0x 0001 0110
#endif


#if 0
#define KEY_TK1_8BIT ((unsigned char)0x12) // �����尴��TK1��8λ��ֵ
#define KEY_TK2_8BIT ((unsigned char)0x34) // �����尴��TK2��8λ��ֵ
#define KEY_TK3_8BIT ((unsigned char)0x56) // �����尴��TK3��8λ��ֵ
#define KEY_TK4_8BIT ((unsigned char)0x78) // �����尴��TK4��8λ��ֵ

#define KEY_TK1_16BIT ((unsigned short)0x1234) // �����尴��TK1��16λ��ֵ
#define KEY_TK2_16BIT ((unsigned short)0x5678) // �����尴��TK2��16λ��ֵ
#define KEY_TK3_16BIT ((unsigned short)0x9ABC) // �����尴��TK3��16λ��ֵ
#define KEY_TK4_16BIT ((unsigned short)0xDEA3) // �����尴��TK4��16λ��ֵ
#endif

/* ����ϵͳ���� *********************************************************************************/
#ifdef DEVELOPMENT_BOARD
/* TK0 ʹ��λ
 * TK0 ͨ��������
 */
#define TK0_CH_EN                       (1)
#define TK0_THR_DATA                    (60)
/*
 * TK1 ʹ��λ
 * TK1 ͨ��������
 */
#define TK1_CH_EN                       (0)
#define TK1_THR_DATA                    (100)
/*
 * TK2 ʹ��λ
 * TK2 ͨ��������
 */
#define TK2_CH_EN                       (0)
#define TK2_THR_DATA                    (100)
/*
 * TK3 ʹ��λ
 * TK3 ͨ��������
 */
#define TK3_CH_EN                       (0)
#define TK3_THR_DATA                    (100)
/*
 * TK4 ʹ��λ
 * TK4 ͨ��������
 */
#define TK4_CH_EN                       (1)
#define TK4_THR_DATA                    (60)
/*
 * TK5 ʹ��λ
 * TK5 ͨ��������
 */
#define TK5_CH_EN                       (1)
#define TK5_THR_DATA                    (69)
/*
 * TK6 ʹ��λ
 * TK6 ͨ��������
 */
#define TK6_CH_EN                       (1)
#define TK6_THR_DATA                    (72)
/*
 * TK7 ʹ��λ
 * TK7 ͨ��������
 */
#define TK7_CH_EN                       (0)
#define TK7_THR_DATA                    (100)
/*
 * TK8 ʹ��λ
 * TK8 ͨ��������
 */
#define TK8_CH_EN                       (0)
#define TK8_THR_DATA                    (100)
/*
 * TK9 ʹ��λ
 * TK9 ͨ��������
 */
#define TK9_CH_EN                       (0)
#define TK9_THR_DATA                    (100)
/*
 * TK10 ʹ��λ
 * TK10 ͨ��������
 */
#define TK10_CH_EN                      (0)
#define TK10_THR_DATA                   (100)
/*
 * TK11 ʹ��λ
 * TK11 ͨ��������
 */
#define TK11_CH_EN                      (0)
#define TK11_THR_DATA                   (100)
/*
 * TK12 ʹ��λ
 * TK12 ͨ��������
 */
#define TK12_CH_EN                      (0)
#define TK12_THR_DATA                   (100)
/*
 * TK13 ʹ��λ
 * TK13 ͨ��������
 */
#define TK13_CH_EN                      (0)
#define TK13_THR_DATA                   (100)
/*
 * TK14 ʹ��λ
 * TK14 ͨ��������
 */
#define TK14_CH_EN                      (0)
#define TK14_THR_DATA                   (100)
/*
 * TK15 ʹ��λ
 * TK15 ͨ��������
 */
#define TK15_CH_EN                      (0)
#define TK15_THR_DATA                   (100)
/*
 * TK16 ʹ��λ
 * TK16 ͨ��������
 */
#define TK16_CH_EN                      (0)
#define TK16_THR_DATA                   (100)
/*
 * TK17 ʹ��λ
 * TK17 ͨ��������
 */
#define TK17_CH_EN                      (0)
#define TK17_THR_DATA                   (100)
/*
 * TK18 ʹ��λ
 * TK18 ͨ��������
 */
#define TK18_CH_EN                      (0)
#define TK18_THR_DATA                   (100)
/*
 * TK19 ʹ��λ
 * TK19 ͨ��������
 */
#define TK19_CH_EN                      (0)
#define TK19_THR_DATA                   (100)
/*
 * TK20 ʹ��λ
 * TK20 ͨ��������
 */
#define TK20_CH_EN                      (0)
#define TK20_THR_DATA                   (100)
/*
 * TK21 ʹ��λ
 * TK21 ͨ��������
 */
#define TK21_CH_EN                      (0)
#define TK21_THR_DATA                   (100)
/*
 * TK22 ʹ��λ
 * TK22 ͨ��������
 */
#define TK22_CH_EN                      (0)
#define TK22_THR_DATA                   (100)
/*
 * TK23 ʹ��λ
 * TK23 ͨ��������
 */
#define TK23_CH_EN                      (0)
#define TK23_THR_DATA                   (100)
/*
 * TK24 ʹ��λ
 * TK24 ͨ��������
 */
#define TK24_CH_EN                      (0)
#define TK24_THR_DATA                   (100)
/*
 * TK25 ʹ��λ
 * TK25 ͨ��������
 */
#define TK25_CH_EN                      (0)
#define TK25_THR_DATA                   (100)
#endif // end ifdef DEVELOPMENT_BOARD


#ifdef CIRCUIT_BOARD

/* TK0 ʹ��λ
 * TK0 ͨ��������
 */
#define TK0_CH_EN                       (1)
#define TK0_THR_DATA                    (50)
/*
 * TK1 ʹ��λ
 * TK1 ͨ��������
 */
#define TK1_CH_EN                       (0)
#define TK1_THR_DATA                    (100)
/*
 * TK2 ʹ��λ
 * TK2 ͨ��������
 */
#define TK2_CH_EN                       (1)
#define TK2_THR_DATA                    (50)
/*
 * TK3 ʹ��λ
 * TK3 ͨ��������
 */
#define TK3_CH_EN                       (1)
#define TK3_THR_DATA                    (50)
/*
 * TK4 ʹ��λ
 * TK4 ͨ��������
 */
#define TK4_CH_EN                       (0)
#define TK4_THR_DATA                    (100)
/*
 * TK5 ʹ��λ
 * TK5 ͨ��������
 */
#define TK5_CH_EN                       (0)
#define TK5_THR_DATA                    (100)
/*
 * TK6 ʹ��λ
 * TK6 ͨ��������
 */
#define TK6_CH_EN                       (0)
#define TK6_THR_DATA                    (100)
/*
 * TK7 ʹ��λ
 * TK7 ͨ��������
 */
#define TK7_CH_EN                       (0)
#define TK7_THR_DATA                    (100)
/*
 * TK8 ʹ��λ
 * TK8 ͨ��������
 */
#define TK8_CH_EN                       (0)
#define TK8_THR_DATA                    (100)
/*
 * TK9 ʹ��λ
 * TK9 ͨ��������
 */
#define TK9_CH_EN                       (1)
#define TK9_THR_DATA                    (50)
/*
 * TK10 ʹ��λ
 * TK10 ͨ��������
 */
#define TK10_CH_EN                      (1)
#define TK10_THR_DATA                   (50)
/*
 * TK11 ʹ��λ
 * TK11 ͨ��������
 */
#define TK11_CH_EN                      (0)
#define TK11_THR_DATA                   (100)
/*
 * TK12 ʹ��λ
 * TK12 ͨ��������
 */
#define TK12_CH_EN                      (0)
#define TK12_THR_DATA                   (100)
/*
 * TK13 ʹ��λ
 * TK13 ͨ��������
 */
#define TK13_CH_EN                      (0)
#define TK13_THR_DATA                   (100)
/*
 * TK14 ʹ��λ
 * TK14 ͨ��������
 */
#define TK14_CH_EN                      (0)
#define TK14_THR_DATA                   (100)
/*
 * TK15 ʹ��λ
 * TK15 ͨ��������
 */
#define TK15_CH_EN                      (0)
#define TK15_THR_DATA                   (100)
/*
 * TK16 ʹ��λ
 * TK16 ͨ��������
 */
#define TK16_CH_EN                      (0)
#define TK16_THR_DATA                   (100)
/*
 * TK17 ʹ��λ
 * TK17 ͨ��������
 */
#define TK17_CH_EN                      (0)
#define TK17_THR_DATA                   (100)
/*
 * TK18 ʹ��λ
 * TK18 ͨ��������
 */
#define TK18_CH_EN                      (0)
#define TK18_THR_DATA                   (100)
/*
 * TK19 ʹ��λ
 * TK19 ͨ��������
 */
#define TK19_CH_EN                      (0)
#define TK19_THR_DATA                   (100)
/*
 * TK20 ʹ��λ
 * TK20 ͨ��������
 */
#define TK20_CH_EN                      (0)
#define TK20_THR_DATA                   (100)
/*
 * TK21 ʹ��λ
 * TK21 ͨ��������
 */
#define TK21_CH_EN                      (0)
#define TK21_THR_DATA                   (100)
/*
 * TK22 ʹ��λ
 * TK22 ͨ��������
 */
#define TK22_CH_EN                      (0)
#define TK22_THR_DATA                   (100)
/*
 * TK23 ʹ��λ
 * TK23 ͨ��������
 */
#define TK23_CH_EN                      (0)
#define TK23_THR_DATA                   (100)
/*
 * TK24 ʹ��λ
 * TK24 ͨ��������
 */
#define TK24_CH_EN                      (1)
#define TK24_THR_DATA                   (75) // �����Ͽ���ʶ����̰���������˫��
// #define TK24_THR_DATA                   (125) // 
// #define TK24_THR_DATA                   (150) // 
// #define TK24_THR_DATA                   (175) // 
// #define TK24_THR_DATA                   (200)
/*
 * TK25 ʹ��λ
 * TK25 ͨ��������
 */
#define TK25_CH_EN                      (0)
#define TK25_THR_DATA                   (100)
#endif


/**************************************************************************************************
*************************ϵͳ��������System configuration area*************************************
***************************************************************************************************/
#define TK_RES_GEAR                     (7)                 // �ŵ����
#define TK_CURR_GEAR                    (75)                // ������
#define TK_DATA_LINE                    (2500)              // ����Ŀ����
#define TK_ADJUST_TIME                  (100)               // ������ʼ��ʱ��(��λ��10ms)
#define TK_MAX_DIFF_VALU                (200)               // ��ʼ������ֵ
// #define TK_MAX_DIFF_VALU                (1000)               // ��ʼ������ֵ
#define TK_ADJUST_EN                    (1)                 // �Ƿ���е���Դ����Ӧ

#endif
/******************************************************************************************/
