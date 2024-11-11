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
#define TK_CH_USE                       ( 5 )                 // ��Ҫʹ�õİ�������


// =======================================================
// ͨ�������ȵ���ֵԽС��������Խ��
// =======================================================
/* TK0 ʹ��λ
 * TK0 ͨ��������
 */
#define TK0_CH_EN                       (0)
#define TK0_THR_DATA                    (200)
/*
 * TK1 ʹ��λ
 * TK1 ͨ��������
 */
#define TK1_CH_EN                       (0)
#define TK1_THR_DATA                    (200)
/*
 * TK2 ʹ��λ
 * TK2 ͨ��������
 */
#define TK2_CH_EN                       (0)
#define TK2_THR_DATA                    (200)
/*
 * TK3 ʹ��λ
 * TK3 ͨ��������
 */
#define TK3_CH_EN                       (0)
#define TK3_THR_DATA                    (200)
/*
 * TK4 ʹ��λ
 * TK4 ͨ��������
 */
#define TK4_CH_EN                       (0)
#define TK4_THR_DATA                    (200)
/*
 * TK5 ʹ��λ
 * TK5 ͨ��������
 */
#define TK5_CH_EN                       (0)
#define TK5_THR_DATA                    (200)
/*
 * TK6 ʹ��λ
 * TK6 ͨ��������
 */
#define TK6_CH_EN                       (0)
#define TK6_THR_DATA                    (200)
/*
 * TK7 ʹ��λ
 * TK7 ͨ��������
 */
#define TK7_CH_EN                       (0)
#define TK7_THR_DATA                    (200)
/*
 * TK8 ʹ��λ
 * TK8 ͨ��������
 */
#define TK8_CH_EN                       (0)
#define TK8_THR_DATA                    (200)
/*
 * TK9 ʹ��λ
 * TK9 ͨ��������
 */
#define TK9_CH_EN                       (0)
#define TK9_THR_DATA                    (200)
/*
 * TK10 ʹ��λ
 * TK10 ͨ��������
 */
#define TK10_CH_EN                      (0)
#define TK10_THR_DATA                   (200)
/*
 * TK11 ʹ��λ
 * TK11 ͨ��������
 */
#define TK11_CH_EN                      (0)
#define TK11_THR_DATA                   (200)
/*
 * TK12 ʹ��λ
 * TK12 ͨ��������
 */
#define TK12_CH_EN                      (0)
#define TK12_THR_DATA                   (200)
/*
 * TK13 ʹ��λ
 * TK13 ͨ��������
 */
#define TK13_CH_EN                      (0)
#define TK13_THR_DATA                   (200)
/*
 * TK14 ʹ��λ
 * TK14 ͨ��������
 */
#define TK14_CH_EN                      (0)
#define TK14_THR_DATA                   (200)
/*
 * TK15 ʹ��λ
 * TK15 ͨ��������
 */
#define TK15_CH_EN                      (1) // ����K5
#define TK15_THR_DATA                   (50)
/*
 * TK16 ʹ��λ
 * TK16 ͨ��������
 */
#define TK16_CH_EN                      (0)
#define TK16_THR_DATA                   (200)
/*
 * TK17 ʹ��λ
 * TK17 ͨ��������
 */
#define TK17_CH_EN                      (1) // ����K4
#define TK17_THR_DATA                   (50)
/*
 * TK18 ʹ��λ
 * TK18 ͨ��������
 */
#define TK18_CH_EN                      (0)
#define TK18_THR_DATA                   (200)
/*
 * TK19 ʹ��λ
 * TK19 ͨ��������
 */
#define TK19_CH_EN                      (0)
#define TK19_THR_DATA                   (200)
/*
 * TK20 ʹ��λ
 * TK20 ͨ��������
 */
#define TK20_CH_EN                      (0)
#define TK20_THR_DATA                   (200)
/*
 * TK21 ʹ��λ
 * TK21 ͨ��������
 */
#define TK21_CH_EN                      (0)
#define TK21_THR_DATA                   (200)
/*
 * TK22 ʹ��λ
 * TK22 ͨ��������
 */
#define TK22_CH_EN                      (0)
#define TK22_THR_DATA                   (200)
/*
 * TK23 ʹ��λ
 * TK23 ͨ��������
 */
#define TK23_CH_EN                      (1) // ����K3
#define TK23_THR_DATA                   (50)
/*
 * TK24 ʹ��λ
 * TK24 ͨ��������
 */
#define TK24_CH_EN                      (1) // ����K1
#define TK24_THR_DATA                   (50) // �����Ͽ���ʶ����̰���������˫��
// #define TK24_THR_DATA                   (125) // 
// #define TK24_THR_DATA                   (150) // 
// #define TK24_THR_DATA                   (175) // 
// #define TK24_THR_DATA                   (200)
/*
 * TK25 ʹ��λ
 * TK25 ͨ��������
 */
#define TK25_CH_EN                      (1) // ����K2
#define TK25_THR_DATA                   (500) // 
// #define TK25_THR_DATA                   (400) // ���и��ʼ�⵽K2����


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
