#ifndef __Debug_Print_h__
#define __Debug_Print_h__
#include <stdio.h>
#include "Debug_MSG.h"

#define DEBUG_PRINT_ENABLE 1
#define DEBUG_PRINT_DISABLE 0

extern int __io_putchar(int ch);

void DebugPrintSwitch(uint8_t state);

#endif //__Debug_Print_h__
