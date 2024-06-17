#include "HandlersCore.h"

HandlersCore_t BPHandlers;

int HandlersCoreInit(uint16_t MapSize)
{
    uint16_t MemSize = MapSize / sizeof(uint32_t) * sizeof(BPHandlersType_t);
    BPHandlers.Handlers = (BPHandlersType_t *)HandlersMalloc(MemSize);
    if (BPHandlers.Handlers == NULL)
    {
        return -1;
    }
    memset(BPHandlers.Handlers, 0, MemSize);
    BPHandlers.Size = MemSize;

    return 0;
}

int BPSetHandler(uint32_t addr, BPHandlersType_t *Handle)
{
    if (!VREG_GOOD_ADDR(addr))
    {
        return -1;
    }
#if (BP_CONF_HANDLERS_EN == 1)
    BPHandlers.Handlers[COUNT(addr)] = *Handle;
#endif
    return 0;
}

int BPGetHandleStart(uint32_t *addr, uint32_t *data)
{
    if (!VREG_GOOD_ADDR(*addr))
    {
        return -1;
    }
    if (BPHandlers.Handlers[COUNT(*addr)].Get == NULL)
    {
        return 0;
    }
    if (BPHandlers.Handlers[COUNT(*addr)].Get(data))
    {
        if (BPHandlers.Handlers[COUNT(*addr)].Err != NULL)
        {
            BPHandlers.Handlers[COUNT(*addr)].Err(addr);
        }
        return -2;
    }
    return 0;
}

int BPSetHandleStart(uint32_t *addr, uint32_t *data)
{
    if (!VREG_GOOD_ADDR(*addr))
    {
        return -1;
    }
    if (BPHandlers.Handlers[COUNT(*addr)].Set == NULL)
    {
        return 0;
    }
    if (BPHandlers.Handlers[COUNT(*addr)].Set(data))
    {
        if (BPHandlers.Handlers[COUNT(*addr)].Err != NULL)
        {
            BPHandlers.Handlers[COUNT(*addr)].Err(addr);
        }
        return -2;
    }
    return 0;
}
