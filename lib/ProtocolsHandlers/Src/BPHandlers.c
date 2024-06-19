#include "BPHandlers.h"

int ReadTestHandlers(uint32_t *arg);
void ErrHandler(uint32_t *arg);
int WriteLockReg(uint32_t *arg);
int BPVersionHandle(uint32_t *RegVal);

int BPHandlersInit(void)
{
    int ret = 0;
    BPHandlersType_t Handlers[32] = {
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = BPVersionHandle, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler},
        {.Get = ReadTestHandlers, .Set = WriteLockReg, .Err = ErrHandler}};
    uint32_t addr = VRS_TIME_HEX;
    for (uint8_t i = 0; i < sizeof(Handlers) / sizeof(Handlers[0]); i++)
    {
        if (BPSetHandler(addr, &Handlers[i]))
        {
            ret = -1;
        }
        
        addr += 4;
    }

    return ret;
}

int BPVersionHandle(uint32_t *RegVal)
{
uint8_t command = (uint8_t)(*RegVal >> 24);
	enum PROJECT_INFO {
		HAL_VERSION,
		CHIP_UID_0,
		CHIP_UID_1,
		CHIP_UID_2,
		CHIP_DEVID,
		CHIP_REVID,
		RTOS_VERSION,
	};

	switch (command) {
	case HAL_VERSION:
		*RegVal = HAL_GetHalVersion();
		break;
	case CHIP_UID_0:
		*RegVal = HAL_GetUIDw0();
		break;
	case CHIP_UID_1:
		*RegVal = HAL_GetUIDw1();
		break;
	case CHIP_UID_2:
		*RegVal = HAL_GetUIDw2();
		break;
	case CHIP_DEVID:
		*RegVal = HAL_GetDEVID();
		break;
	case CHIP_REVID:
		*RegVal = HAL_GetREVID();
		break;
	case RTOS_VERSION:
		*RegVal = (tskKERNEL_VERSION_MAJOR << 16) |
			  (tskKERNEL_VERSION_MINOR << 8) |
			  (tskKERNEL_VERSION_BUILD);
		break;
	default:
		return -1;
	}
    printf("VRS::\t0x%08lx\r\n", *RegVal);
    return 0;
}

int ReadTestHandlers(uint32_t *arg)
{

    printf("Read::\t0x%08lx\r\n", *arg);
    return 0;
}

void ErrHandler(uint32_t *arg)
{
    printf("Reg::\t0x%08lx\r\n", *arg);
}

int WriteLockReg(__attribute__((unused)) uint32_t *arg)
{
    printf("Lock\r\n");
    return 1;
}