#ifndef __BPCDCport_h__
#define __BPCDCport_h__
#include "BProt.h"

extern int UsbCdcTransmit(uint8_t *Data, uint32_t Len);
void CdcRecievCallBack(uint8_t *data, uint16_t size);
#endif //__BPCDCport_h__