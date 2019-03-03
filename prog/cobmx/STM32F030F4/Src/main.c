/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint16_t sens_analog = 0;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
     char buffer[16];
    int i = 0;
    int sec = 0;
    int  flag_ON_OFF = 0;
    uint8_t M1[2] = {'M', '0'};

    uint8_t data_1[4] = {0};




    if((HAL_GPIO_ReadPin(GPIOA, bit_0_Pin)==GPIO_PIN_RESET) &&
    		(HAL_GPIO_ReadPin(GPIOA, bit_1_Pin)==GPIO_PIN_RESET) &&
			(HAL_GPIO_ReadPin(GPIOA, bit_2_Pin)==GPIO_PIN_RESET) )

                  {
    	             M1[0] ='M';
    	             M1[1] ='1';
                  }
    if((HAL_GPIO_ReadPin(GPIOA, bit_0_Pin)==GPIO_PIN_SET) &&
       		(HAL_GPIO_ReadPin(GPIOA, bit_1_Pin)==GPIO_PIN_RESET) &&
   			(HAL_GPIO_ReadPin(GPIOA, bit_2_Pin)==GPIO_PIN_RESET) )

                     {
    	                     M1[0] ='M';
    	    	             M1[1] ='2';
                     }
    if((HAL_GPIO_ReadPin(GPIOA, bit_0_Pin)==GPIO_PIN_RESET) &&
           		(HAL_GPIO_ReadPin(GPIOA, bit_1_Pin)==GPIO_PIN_SET) &&
       			(HAL_GPIO_ReadPin(GPIOA, bit_2_Pin)==GPIO_PIN_RESET) )

                         {
    	                     M1[0] ='M';
    	    	             M1[1] ='3';
                         }
    if((HAL_GPIO_ReadPin(GPIOA, bit_0_Pin)==GPIO_PIN_SET) &&
              		(HAL_GPIO_ReadPin(GPIOA, bit_1_Pin)==GPIO_PIN_SET) &&
          			(HAL_GPIO_ReadPin(GPIOA, bit_2_Pin)==GPIO_PIN_RESET) )

                            {
    	                     M1[0] ='M';
    	    	             M1[1] ='4';
                            }
    if((HAL_GPIO_ReadPin(GPIOA, bit_0_Pin)==GPIO_PIN_RESET) &&
                 		(HAL_GPIO_ReadPin(GPIOA, bit_1_Pin)==GPIO_PIN_RESET) &&
             			(HAL_GPIO_ReadPin(GPIOA, bit_2_Pin)==GPIO_PIN_SET) )

                               {
    	                     M1[0] ='M';
    	    	             M1[1] ='5';
                               }

    HAL_UART_Transmit(&huart1, M1, 2, 500);

    uint8_t data_srav[4] ={ M1[0], M1[1], '1', '\n'};
    uint8_t data_srav_off[4] = {M1[0],  M1[1], '0', '\n'};
    char flag_uart = 0;

    while (1)
    {

        HAL_UART_Receive(&huart1, data_1, 4, 15);

        if (huart1.RxXferCount == 0)
        {
        	flag_uart = 1;
        	sec = 0;
            //HAL_UART_Transmit(&huart1, data_1, 4, 500);
            if ((data_1[0] == data_srav[0]) & (data_1[1] == data_srav[1]) & (data_1[2] == data_srav[2]) & (data_1[3] == data_srav[3]))
            {
                flag_ON_OFF = 1;
                HAL_UART_Transmit(&huart1, data_1, 4, 500);
            }
            if ((data_1[0] == data_srav_off[0]) & (data_1[1] == data_srav_off[1]) & (data_1[2] == data_srav_off[2]) & (data_1[3] == data_srav_off[3]))
            {
                flag_ON_OFF = 0;
                HAL_UART_Transmit(&huart1, data_1, 4, 500);
            }

        }




        if (((HAL_GetTick() - i) > 100)  ) // ЩИТАЕМ КОЛИЧЕСТВО СЕКУНД
        {
            i = HAL_GetTick();
            sec++;
            //HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer, "-------\n"), 500);
           // HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer, "%d\n", sens_analog), 500);
           // HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer, "second = %d\n", sec), 500);
            if (sec > 600 ){
            	flag_uart = 0;
            }
        }


        if (flag_ON_OFF == 1){
        	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
        	HAL_ADC_Start(&hadc);                  // запуск аналоговоко
        	HAL_ADC_PollForConversion(&hadc, 100); // запуск преобразований
        	sens_analog = HAL_ADC_GetValue(&hadc); // считываем данные
        	HAL_ADC_Stop(&hadc);                   // остановка ацп
        	if ( sens_analog > 400 )
             {
        	HAL_UART_Transmit(&huart1, M1, 2, 10);
        	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer, "%d\n", sens_analog), 5);
             }
        }
        else {
        	HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
        }



        if (((sec > 1) & (flag_uart == 0))||(sec > 600 ) )
        {

            MX_RTC_Init(); // запускаем rts будильник
                // сон -------------------------------------
            //HAL_Delay(500);
            sec = 0;
            __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
            HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
            HAL_PWR_EnterSTANDBYMode();
            HAL_ResumeTick();

            //--------------------------------------------------
        }
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14
                              |RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
