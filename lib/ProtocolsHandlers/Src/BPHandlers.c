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
    printf("VRS::0x%lx", *RegVal);
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

int WriteLockReg(__attribute__((unused))uint32_t *arg)
{
    printf("Lock\r\n");
    return 1;
}