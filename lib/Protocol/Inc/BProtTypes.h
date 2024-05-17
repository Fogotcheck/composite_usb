#ifndef __BProtTypes_h__
#define __BProtTypes_h__

#include "BProtConf.h"

typedef struct BPHead
{
    uint32_t dest;
    uint32_t source;
    uint16_t len;
    uint16_t type;
    uint16_t tag;
    uint16_t crc;
} BPHead_t;

typedef struct BPFrame
{
    BPHead_t *head;
    uint32_t *data;
    uint32_t * xor ;
} BPFrame_t;

typedef struct BPmsgTypeConf
{
    uint8_t BPMode;
#if defined(BP_CONF_SLAVE_MODE_EN)
#endif
#if defined(BP_CONF_MASTER_MODE_EN)
#endif
#if defined(BP_CONF_TRANSIT_MODE_EN)
#endif
} BPmsgTypeConf_t;

typedef struct BPBuf
{
    uint8_t data[BP_CONF_MAX_LEN_MSG];
    uint16_t size;
    BPmsgTypeConf_t MsgConf;
} BPBuf_t;

#endif //__BProtTypes_h__
