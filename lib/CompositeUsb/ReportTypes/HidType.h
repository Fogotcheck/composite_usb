#ifndef __HidType_h__
#define __HidType_h__


typedef struct Stick
{
	uint16_t X;	 // Данные оси X первого стика (12 бит)
	uint16_t Y;	 // Данные оси Y первого стика (12 бит)
	uint16_t Z;	 // Данные оси X второго стика (12 бит)
	uint16_t rX; // Данные оси Y второго стика (12 бит)
	uint16_t rY; // Данные оси X третьего стика (12 бит)
	uint16_t rZ; // Данные оси Y третьего стика (12 бит)

} Stick_t;

typedef struct Slider
{
	uint16_t L; // Данные оси X двухосевого стика (12 бит)
	uint16_t R; // Данные оси Y двухосевого стика (12 бит)
} Slider_t;

#pragma pack(push, 1)
typedef struct HIDReport
{

	uint32_t Buttons;
	Stick_t Stick;
	Slider_t Slider;
	uint8_t wake;

} HIDReport_t;
#pragma pack(pop)

#endif //__HidType_h__