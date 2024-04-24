#ifndef __CompositeUsb_h__
#define __CompositeUsb_h__

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"
#include "CdcType.h"
#include "HidType.h"

#define USB_CDC_QUEUE_LEN 6

int CompositeUsbInit(void);
#endif //__CompositeUsb_h__