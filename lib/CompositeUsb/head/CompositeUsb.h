#ifndef __CompositeUsb_h__
#define __CompositeUsb_h__

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
#include "queue.h"
#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"
#include "CdcType.h"
#include "HidType.h"
#include "usb_events.h"

#define USB_CDC_QUEUE_LEN 6
#define USB_BINTERVAL_MS 5 
#define USB_WAIT_EVENT_TIME_MS 10
#define USB_THREAD_PRIORITY 4


int CompositeUsbInit(void);
int UsbCdcTransmit(uint8_t *Buf, uint32_t Len);
#endif //__CompositeUsb_h__