/**
  ******************************************************************************
  * @file    debug.h
  * @author  HUGE-IC Application Team
  * @version V1.0.0
  * @date    01-05-2021
  * @brief   Main program body header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 HUGE-IC</center></h2>
  *
  *
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// ʹ��%d��ӡ����ֵ����ʱ����ע�⣺
// ��ʽ------����----------�������
// % d--- �����ֽڱ��� ---- int
// %bd--- �����ֽڱ��� ---- char
// %ld--- �ĸ��ֽڱ��� ---- long int

#define DBG_PRINTF_EN           (0)             // 0:���ñ�׼printf()����, 1:ʹ�ܱ�׼printf()����

#define DEBUG_BAUD              (115200UL)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
     
/** @addtogroup Template_Project
  * @{
  */

/** @addtogroup DEBUG
  * @{
  */ 

     
/** @defgroup DEBUG_Exported_Constants
  * @{
  */
/**
  * @}
  */


/** @defgroup DEBUG_Exported_Functions
  * @{
  */
  

/**
  * @brief  Debug puchar function
  * @param  uart_data : Data that needs to be sent
  * @retval None
  */
void debug_putchar(u8 uart_data);

/**
  * @brief  Debug initialization function
  * @param  None
  * @retval None
  */
void debug_init(void);

/**
  * @brief  Debug User printf function
  * @param  p_data : The string to send
  * @retval None
  */
void user_printf(char *p_data);


/**
  * @}
  */ 


#ifdef __cplusplus
}
#endif

#endif //__DEBUG_H__

/**
  * @}
  */

/**
  * @}
  */

/*************************** (C) COPYRIGHT 2021 HUGE-IC ***** END OF FILE *****/