#ifndef __HandlersCore_h__
#define __HandlersCore_h__

#include "string.h"

#include "stdlib.h"
#define HandlersMalloc(MemSize) malloc(MemSize)

#include "VReg.h"
#include "BProtConf.h"

typedef int(Handlers_t)(uint32_t *);
typedef void(ErrHandlers_t)(uint32_t *);

typedef struct BPHandlersType
{
    Handlers_t *Get;
    Handlers_t *Set;
    ErrHandlers_t *Err;
} BPHandlersType_t;

typedef struct HandlersCore
{
    BPHandlersType_t *Handlers;
    uint16_t Size;
} HandlersCore_t;

int HandlersCoreInit(uint16_t MapSize);
int BPSetHandler(uint32_t addr, BPHandlersType_t *Handle);
int BPGetHandleStart(uint32_t *addr, uint32_t *data);
int BPSetHandleStart(uint32_t *addr, uint32_t *data);

#endif //__HandlersCore_h__