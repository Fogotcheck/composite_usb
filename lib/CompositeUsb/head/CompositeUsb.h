#ifndef __CompositeUsb_h__
#define __CompositeUsb_h__

#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
#include "queue.h"

#include "CdcType.h"
#include "HidType.h"
#include "usb_events.h"

#include "Debug_MSG.h"

#define USB_CDC_QUEUE_LEN 6
#define USB_BINTERVAL_MS 5 // when use OPT_OS_FREERTOS may be any
#define USB_WAIT_EVENT_TIME_MS 10
#define USB_THREAD_PRIORITY 4

enum COMPOSITE_USB_ITF_EVENTS
{
    USB_HID_EMPTY = (uint32_t)(1 << 0),
    USB_CDC_EMPTY = (uint32_t)(1 << 1),
    USB_ALL_EVENTS = (uint32_t)(USB_HID_EMPTY | USB_CDC_EMPTY)
};

int CompositeUsbInit(void);
int UsbCdcTransmit(uint8_t *Buf, uint32_t Len);
int UsbHidTransmit(uint8_t *Data, uint32_t Len);
#endif //__CompositeUsb_h__