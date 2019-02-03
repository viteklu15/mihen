/**
  ******************************************************************************
  * @file    stm32f0xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    03-Oct-2014
  * @brief   Header file of GPIO HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_GPIO_EX_H
#define __STM32F0xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx Extended HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */ 
  
/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */
  
// #if defined (STM32F030x6)
// STM32F030F4
#if 1
/*------------------------- STM32F030x6---------------------------*/ 
/* AF 0 */
#define GPIO_AF0_EVENTOUT     ((uint8_t)0x00)  /*!< AF0: EVENTOUT Alternate Function mapping  */
#define GPIO_AF0_MCO          ((uint8_t)0x00)  /*!< AF0: MCO Alternate Function mapping       */
#define GPIO_AF0_SPI1         ((uint8_t)0x00)  /*!< AF0: SPI1 Alternate Function mapping      */
#define GPIO_AF0_TIM17        ((uint8_t)0x00)  /*!< AF0: TIM17 Alternate Function mapping     */
#define GPIO_AF0_SWDIO        ((uint8_t)0x00)  /*!< AF0: SWDIO Alternate Function mapping     */
#define GPIO_AF0_SWCLK        ((uint8_t)0x00)  /*!< AF0: SWCLK Alternate Function mapping     */
#define GPIO_AF0_TIM14        ((uint8_t)0x00)  /*!< AF0: TIM14 Alternate Function mapping     */
#define GPIO_AF0_USART1       ((uint8_t)0x00)  /*!< AF0: USART1 Alternate Function mapping    */
#define GPIO_AF0_IR           ((uint8_t)0x00)  /*!< AF0: IR Alternate Function mapping        */

/* AF 1 */
#define GPIO_AF1_TIM3         ((uint8_t)0x01)  /*!< AF1: TIM3 Alternate Function mapping      */
#define GPIO_AF1_USART1       ((uint8_t)0x01)  /*!< AF1: USART1 Alternate Function mapping    */
#define GPIO_AF1_EVENTOUT     ((uint8_t)0x01)  /*!< AF1: EVENTOUT Alternate Function mapping  */
#define GPIO_AF1_I2C1         ((uint8_t)0x01)  /*!< AF1: I2C1 Alternate Function mapping      */

/* AF 2 */
#define GPIO_AF2_TIM1         ((uint8_t)0x02)  /*!< AF2: TIM1 Alternate Function mapping      */
#define GPIO_AF2_TIM16        ((uint8_t)0x02)  /*!< AF2: TIM16 Alternate Function mapping     */
#define GPIO_AF2_TIM17        ((uint8_t)0x02)  /*!< AF2: TIM17 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT     ((uint8_t)0x02)  /*!< AF2: EVENTOUT Alternate Function mapping  */

/* AF 3 */
#define GPIO_AF3_EVENTOUT     ((uint8_t)0x03)  /*!< AF3: EVENTOUT Alternate Function mapping  */
#define GPIO_AF3_I2C1         ((uint8_t)0x03)  /*!< AF3: I2C1 Alternate Function mapping      */

/* AF 4 */
#define GPIO_AF4_TIM14        ((uint8_t)0x04)  /*!< AF4: TIM14 Alternate Function mapping     */
#define GPIO_AF4_I2C1         ((uint8_t)0x04)  /*!< AF4: I2C1 Alternate Function mapping      */

/* AF 5 */
#define GPIO_AF5_TIM16        ((uint8_t)0x05)  /*!< AF5: TIM16 Alternate Function mapping     */
#define GPIO_AF5_TIM17        ((uint8_t)0x05)  /*!< AF5: TIM17 Alternate Function mapping     */

/* AF 6 */
#define GPIO_AF6_EVENTOUT     ((uint8_t)0x06)  /*!< AF6: EVENTOUT Alternate Function mapping  */

#define IS_GPIO_AF(AF)        ((AF) <= (uint8_t)0x06)

#endif /* STM32F030x6 */

/*---------------------------------- STM32F030x8 -------------------------------------------*/
// #if defined (STM32F030x8)
#if 0
/* AF 0 */
#define GPIO_AF0_EVENTOUT     ((uint8_t)0x00)  /*!< AF0: EVENTOUT Alternate Function mapping  */
#define GPIO_AF0_MCO          ((uint8_t)0x00)  /*!< AF0: MCO Alternate Function mapping       */
#define GPIO_AF0_SPI1         ((uint8_t)0x00)  /*!< AF0: SPI1 Alternate Function mapping      */
#define GPIO_AF0_SPI2         ((uint8_t)0x00)  /*!< AF0: SPI2 Alternate Function mapping      */
#define GPIO_AF0_TIM15        ((uint8_t)0x00)  /*!< AF0: TIM15 Alternate Function mapping     */
#define GPIO_AF0_TIM17        ((uint8_t)0x00)  /*!< AF0: TIM17 Alternate Function mapping     */
#define GPIO_AF0_SWDIO        ((uint8_t)0x00)  /*!< AF0: SWDIO Alternate Function mapping     */
#define GPIO_AF0_SWCLK        ((uint8_t)0x00)  /*!< AF0: SWCLK Alternate Function mapping     */
#define GPIO_AF0_TIM14        ((uint8_t)0x00)  /*!< AF0: TIM14 Alternate Function mapping     */
#define GPIO_AF0_USART1       ((uint8_t)0x00)  /*!< AF0: USART1 Alternate Function mapping    */
#define GPIO_AF0_IR           ((uint8_t)0x00)  /*!< AF0: IR Alternate Function mapping        */

/* AF 1 */
#define GPIO_AF1_TIM3         ((uint8_t)0x01)  /*!< AF1: TIM3 Alternate Function mapping      */
#define GPIO_AF1_TIM15        ((uint8_t)0x01)  /*!< AF1: TIM15 Alternate Function mapping     */
#define GPIO_AF1_USART1       ((uint8_t)0x01)  /*!< AF1: USART1 Alternate Function mapping    */
#define GPIO_AF1_USART2       ((uint8_t)0x01)  /*!< AF1: USART2 Alternate Function mapping    */
#define GPIO_AF1_EVENTOUT     ((uint8_t)0x01)  /*!< AF1: EVENTOUT Alternate Function mapping  */
#define GPIO_AF1_I2C1         ((uint8_t)0x01)  /*!< AF1: I2C1 Alternate Function mapping      */
#define GPIO_AF1_I2C2         ((uint8_t)0x01)  /*!< AF1: I2C2 Alternate Function mapping      */
#define GPIO_AF1_IR           ((uint8_t)0x01)  /*!< AF1: IR Alternate Function mapping        */

/* AF 2 */
#define GPIO_AF2_TIM1         ((uint8_t)0x02)  /*!< AF2: TIM1 Alternate Function mapping      */
#define GPIO_AF2_TIM16        ((uint8_t)0x02)  /*!< AF2: TIM16 Alternate Function mapping     */
#define GPIO_AF2_TIM17        ((uint8_t)0x02)  /*!< AF2: TIM17 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT     ((uint8_t)0x02)  /*!< AF2: EVENTOUT Alternate Function mapping  */

/* AF 3 */
#define GPIO_AF3_EVENTOUT     ((uint8_t)0x03)  /*!< AF3: EVENTOUT Alternate Function mapping  */
#define GPIO_AF3_I2C1         ((uint8_t)0x03)  /*!< AF3: I2C1 Alternate Function mapping      */
#define GPIO_AF3_TIM15        ((uint8_t)0x03)  /*!< AF3: TIM15 Alternate Function mapping     */

/* AF 4 */
#define GPIO_AF4_TIM14        ((uint8_t)0x04)  /*!< AF4: TIM14 Alternate Function mapping     */

/* AF 5 */
#define GPIO_AF5_TIM16        ((uint8_t)0x05)  /*!< AF5: TIM16 Alternate Function mapping     */
#define GPIO_AF5_TIM17        ((uint8_t)0x05)  /*!< AF5: TIM17 Alternate Function mapping     */

/* AF 6 */
#define GPIO_AF6_EVENTOUT     ((uint8_t)0x06)  /*!< AF6: EVENTOUT Alternate Function mapping  */

#define IS_GPIO_AF(AF)        ((AF) <= (uint8_t)0x06)

#endif /* STM32F030x8 */


/**
  * @}
  */ 

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @defgroup GPIOEx_Get_Port_Index GPIOEx_Get Port Index
* @{
  */
#if defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
    defined (STM32F091xC) || defined (STM32F098xx)
#define GET_GPIO_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U :\
                                      ((__GPIOx__) == (GPIOE))? 4U : 5U)
#endif

#if defined (STM32F030x6) || defined (STM32F030x8) || \
    defined (STM32F051x8) || defined (STM32F058xx)
#define GET_GPIO_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U : 5U)
#endif

#if defined (STM32F031x6) || defined (STM32F038xx) || \
    defined (STM32F042x6) || defined (STM32F048xx)
#define GET_GPIO_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U : 5U)
#endif

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/ 
/**
  * @}
  */ 

/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

