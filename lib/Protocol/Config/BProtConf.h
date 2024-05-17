#ifndef __BProtConf_h__
#define __BProtConf_h__

#include "VRegMap.h"

#define BP_CONF_SYSTEM_REGS_EN
#if defined(BP_CONF_SYSTEM_REGS_EN)
#define VRS_COMPILE_TIME VRS_VERSION
#define VRS_MEMORY_SIZE VRS_SIZE
#define VRS_ERRORS_COUNT VRS_ERR
#endif

#define BP_CONF_MAX_LEN_MSG 128
#define BP_CONF_SLAVE_MODE_EN
#define BP_CONF_MASTER_MODE_EN
#define BP_CONF_TRANSIT_MODE_EN

#define MY_ADDRESS 0x12340000

#endif //__BProtConf_h__