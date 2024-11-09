// GPIO���õ�Դ�ļ�
#include "my_gpio.h"

// ������ų�ʼ���������ã�
// P1_1
void output_pin_init(void)
{
    P1_MD0 &= ~(GPIO_P11_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P1_MD0 |= GPIO_P11_MODE_SEL(0x1);    // ����Ϊ���ģʽ

    FOUT_S11 = GPIO_FOUT_AF_FUNC; // ѡ��AF�������

    // λ����
    P11 = 1;
}

/**
 * @brief P12����Ϊ���ģʽ
*/
void p12_output_config(void)
{
    P1_MD0 &= ~(GPIO_P12_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P1_MD0 |= GPIO_P12_MODE_SEL(0x1);    // ����Ϊ���ģʽ

    FOUT_S12 = GPIO_FOUT_AF_FUNC; // ѡ��AF�������

    P1_PU |= GPIO_P12_PULL_UP(0x01); // �ڲ�����������
    P1_PD |= GPIO_P12_PULL_PD(0x01); // �ڲ�����������
    // �����������������������ž��൱�ڸ���״̬��ͬʱ�ܹ�����һЩ��·�ĸ���

    // λ����
    P12 = 1;
}


/**
 * @brief P01����Ϊ���ģʽ
 *        P01�ڿ����������ӵ���LED6������
*/
void p01_output_config(void)
{
    P0_MD0 &= ~(GPIO_P01_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P0_MD0 |= GPIO_P01_MODE_SEL(0x1);    // ����Ϊ���ģʽ

    FOUT_S01 = GPIO_FOUT_AF_FUNC; // ѡ��AF�������

    P0_PU |= GPIO_P01_PULL_UP(0x01); // �ڲ�����������
    P0_PD |= GPIO_P01_PULL_PD(0x01); // �ڲ�����������
    // �����������������������ž��൱�ڸ���״̬��ͬʱ�ܹ�����һЩ��·�ĸ���

    // λ����
    P01 = 0;
}


/**
 * @brief P26����Ϊ���ģʽ
*/
void p26_output_config(void)
{
    P2_MD1 &= ~(GPIO_P26_MODE_SEL(0x1)); // ��Ӧ�ļĴ���������
    P2_MD1 |= GPIO_P26_MODE_SEL(0x1);    // ����Ϊ���ģʽ

    FOUT_S26 = GPIO_FOUT_AF_FUNC; // ѡ��AF�������

    P2_PU |= GPIO_P26_PULL_UP(0x01); // �ڲ�����������
    P2_PD |= GPIO_P26_PULL_PD(0x01); // �ڲ�����������
    // �����������������������ž��൱�ڸ���״̬��ͬʱ�ܹ�����һЩ��·�ĸ���

    // λ����
    P26 = 0;
}



