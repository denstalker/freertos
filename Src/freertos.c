/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "st7789.h"
#include "adc.h"
#include <stdio.h>
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
/* USER CODE BEGIN Variables */
int a = 0;
char buff[16] = {0,};
char str[60] = {'A','B'};
float adc_read = 0;
char pcWriteBuffer[256];


/* USER CODE END Variables */
/* Definitions for topTask */
osThreadId_t topTaskHandle;
const osThreadAttr_t topTask_attributes = {
  .name = "topTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTopTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationIdleHook(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of topTask */
  topTaskHandle = osThreadNew(StartTopTask, NULL, &topTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
   ST7789_Init(240,240);
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTopTask */
/**
  * @brief  Function implementing the topTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartTopTask */
void StartTopTask(void *argument)
{
  /* USER CODE BEGIN StartTopTask */
  /* Infinite loop */
  for(;;)
  {
    vTaskGetRunTimeStats(pcWriteBuffer);
    osDelay(1000);
  }
  /* USER CODE END StartTopTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {




      char *tmpSign = (adc_read < 0) ? "-" : "";
      float tmpVal = (adc_read < 0) ? -adc_read : adc_read;

      int tmpInt1 = tmpVal;                  // Get the integer (678).
      float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
      int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

      // Print as parts, note that you need 0-padding for fractional bit.

      sprintf (str, "adc_read = %s%d.%04d", tmpSign, tmpInt1, tmpInt2);


//      ST7789_print_5x8(10, 30, RED, RGB565(0, 0, 0), 0, "Я");
//      osDelay(1);
//      ST7789_print_5x8(40, 60, WHITE, RGB565(0, 0, 0), 0, "Твой ");
//      osDelay(1);
//      ST7789_print_5x8(40, 80, YELLOW, RGB565(0, 0, 0), 0, "Служба");
//      osDelay(1);
//      ST7789_print_5x8(40, 100, MAGENTA, RGB565(0, 0, 0), 0, "Труба");
//      osDelay(1);
//      ST7789_print_5x8(40, 120, GREEN, RGB565(0, 0, 0), 0, "ШАТАЛ ");
//      osDelay(1);
//      ST7789_print_5x8(40, 140, CYAN, RGB565(0, 0, 0), 0, "=) ");

      osDelay(1);
      ST7789_print_7x11(40, 160, YELLOW, RGB565(0, 0, 0), 0,str);
      ST7789_print_7x11(0, 10, WHITE, RGB565(0, 0, 0), 0,pcWriteBuffer);


      osDelay(100);

  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {


      HAL_ADC_Start(&hadc1);
      HAL_ADC_PollForConversion(&hadc1,100);
      adc_read =((float)HAL_ADC_GetValue(&hadc1))*3/4096;

      HAL_ADC_Stop(&hadc1);


      osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
