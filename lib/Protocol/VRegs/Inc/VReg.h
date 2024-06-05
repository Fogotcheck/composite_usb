#ifndef __VReg_h__
#define __VReg_h__

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "BProtConf.h"

typedef struct VRegData
{
    uint8_t *mem;
    uint16_t size;
} VRegData_t;

extern VRegData_t VRMap;

#define VREG_GOOD_ALIGN(x) (!((x) % (sizeof(uint32_t))))
#define VREG_GOOD_RANGE(x) ((x) < (VRMap.size) ? 1 : 0)

#define VREG_GOOD_ADDR(x) (VREG_GOOD_RANGE(x) && VREG_GOOD_ALIGN(x))

#define VAL(addr) (*(uint32_t *)(VRMap.mem + (uint32_t)(addr)))

#define VR_OFSETT_SHIFT_BIT (VIRT_REG_USER_WORD_SIZE >> 1)
#define COUNT(addr) (addr >> VR_OFSETT_SHIFT_BIT)

int VRMapInit(void *PtrRegMap, uint16_t MapSize);
int VRSetData(uint32_t *addr, uint32_t *data);
int VRGetData(uint32_t *addr, uint32_t *data);

#endif //__VReg_h__