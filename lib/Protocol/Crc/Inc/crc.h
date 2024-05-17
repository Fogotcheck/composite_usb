#ifndef __CRC_H__
#define __CRC_H__
#include <stdint.h>

/*Функция вычисляет crc16 по полиному таблицы полиномов
загружены в FLASH */
uint16_t crc16(uint8_t *buffer, uint16_t count);
/*Функция вычисляет crc8 по полиному таблицы полиномов
загружены в FLASH */
uint8_t crc8(uint8_t *buffer, uint16_t count);

uint32_t xor32(uint32_t *buffer, uint16_t count);
#endif //__CRC_H__
