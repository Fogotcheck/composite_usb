#ifndef __BProt_h__
#define __BProt_h__

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#if defined(USE_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"

#define BPROT_THR_STACK 256
#define BPROT_THR_PRIORITY 8
#endif

#include "BProtTypes.h"
#include "BProtDef.h"
#include "VReg.h"
#include "crc.h"

extern QueueHandle_t BPQueue;

int BProtInit(void *PtrRegMap, uint16_t MapSize);
void BProtMsgHandler(BPBuf_t *Buf);
void BPTransmitCallBack(uint8_t *data, uint16_t size);
void BPErrHandler(void);
#endif //__BProt_h__