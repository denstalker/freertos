#!/bin/bash

rm Drivers/STM32F1xx_HAL_Driver/Inc/stm32_assert_template.h
rm Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_conf_template.h
rm Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_msp_template.c
rm Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_timebase_rtc_alarm_template.c
rm Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_timebase_tim_template.c

rm Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_1.c
rm Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_2.c
rm Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_3.c
rm Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_5.c


cd build
rm ./-std=gnu99
rm -rf *

cmake ..
cmake --build . -- -j4