#ifndef __VirtComPort_h__
#define __VirtComPort_h__

#include "FreeRTOS.h"
#include "task.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

int VirtComPortInit(void);
#endif //__VirtComPort_h__