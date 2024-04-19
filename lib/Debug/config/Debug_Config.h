#ifndef __Debug_Config_h__
#define __Debug_Config_h__

#if defined(STM32WB55xx)
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_uart_ex.h"
#include "stm32wbxx_hal_uart.h"
#endif

extern UART_HandleTypeDef huart1;
#endif //__Debug_Config_h__
