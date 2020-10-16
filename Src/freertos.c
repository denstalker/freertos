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
#include "st7789.h"

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
/* USER CODE BEGIN Variables */
int a = 0;
    uint8_t buff[16] = {0,};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .priority = (osPriority_t) osPriorityLow,
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

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
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
    taskENTER_CRITICAL();
    ST7789_Init(240, 240);
	  // Инициализация входа для кнопки
    // Тест вывода основных цветов
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		
    uint16_t color = RGB565(255, 0, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);
  
    color = RGB565(0, 255, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(50, 55, 50);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(0, 0, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 255, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 0, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(0, 255, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 255, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);
		
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		
		for (uint8_t y = 0; y<240 ; y++) {
			ST7789_DrawLine(120, 120, 239, y, RGB565(y+10, 0, 0));
		}
   		
		for (uint8_t x = 0; x<240 ; x++) {
			ST7789_DrawLine(120, 120, x, 239, RGB565(0, x+10, 0));
		}
   
		for (uint8_t y = 0; y<240 ; y++) {
			ST7789_DrawLine(120, 120, 0, y, RGB565(0, 0, y+10));
		}
 
		for (uint8_t x = 0; x<240 ; x++) {
			ST7789_DrawLine(120, 120, x, 0, RGB565(x+10, x+10, x+10));
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);

    for (uint8_t x = 0; x < 240 ; x = x + 20) {
			for (uint8_t y = 0; y < 240; y = y + 20) {
				ST7789_DrawRectangleFilled(x + 3, y + 3, x + 17, y + 17, RGB565(x, y, 0));
				ST7789_DrawRectangle(x + 2, y + 2, x + 19, y + 19, RGB565(250, 250, 250));
			}
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);

    for (uint8_t x = 0; x < 240 ; x = x + 20) {
			for (uint8_t y = 0; y < 240; y = y + 20) {
        ST7789_DrawCircleFilled(x + 10, y + 10, 8, RGB565(x, y, 0));
        ST7789_DrawCircle(x + 10, y + 10, 9, RGB565(0, y, x));
			}
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
    taskEXIT_CRITICAL();
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

     HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    osDelay(1000);
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
