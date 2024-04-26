#include "Debug_Config.h"
#include "Debug_Print.h"

UART_HandleTypeDef *DebugUart = &huart1;

static uint8_t DebugPrintEn = 0;

int DebugTerminal_send(uint8_t data);

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
	DebugTerminal_send(ch);
	return 1;
}

/*!
Функция переключатель для отправки данных
 \param[in] state DEBUG_PRINT_ENABLE = 1
*/
void DebugPrintSwitch(uint8_t state)
{
	if (state == DEBUG_PRINT_DISABLE)
	{
		DebugPrintEn = DEBUG_PRINT_ENABLE;
		D_STATE_INFO;
	}
	DebugPrintEn = state;
}

int DebugTerminal_send(uint8_t data)
{
	if (DebugPrintEn != DEBUG_PRINT_ENABLE)
	{
		return 0;
	}

	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(DebugUart, &data, 1, 5);
	if (ret == HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
