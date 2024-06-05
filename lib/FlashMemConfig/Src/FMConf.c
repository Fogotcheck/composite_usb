#include "FMConf.h"

extern const uint8_t FMConf_start[] asm("_binary_" __BINARY_PATH "_start");
extern const uint8_t FMConf_end[] asm("_binary_" __BINARY_PATH "_end ");
extern const uint8_t FMConf_size[] asm("_binary_" __BINARY_PATH "_size");

extern UART_HandleTypeDef huart1;

void Test(void)
{
	__attribute__((unused)) uint32_t tmp = (uint32_t)FMConf_size;
	// HAL_UART_Transmit(&huart1, FMConf_start, tmp, 10);
	printf("%s\r\n", FMConf_start);
}
