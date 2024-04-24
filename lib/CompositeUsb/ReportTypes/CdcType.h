#ifndef __CdcType_h__
#define __CdcType_h__
#include "tusb_config.h"

typedef struct CdcReport
{
    uint8_t DType;
    uint8_t Data[CFG_TUD_CDC_TX_BUFSIZE];
    uint32_t Size;
} CdcReport_t;

enum CDC_DATA_TYPE
{
    CDC_TX,
    CDC_RX,
};

#endif //__CdcType_h__