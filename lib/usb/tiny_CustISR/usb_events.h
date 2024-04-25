#ifndef __usb_events_h__
#define __usb_events_h__

#define FREERTOS_MAX_EVENT_SIZE 24

enum COMPOSITE_USB_ISR_EVENTS
{
    USB_MOUNT = (uint32_t)(1 << 0),
    USB_UMOUNT = (uint32_t)(1 << 1),
    USB_SUSPEND = (uint32_t)(1 << 2),
    USB_RESUME = (uint32_t)(1 << 3),
    // USB_HID_EVENTS
    USB_HID_CPLT_TX = (uint32_t)(1 << 4),
    // USB_CDC_EVENTS
    USB_CDC_RX = (uint32_t)(1 << 5),
    USB_CDC_CPLT_TX = (uint32_t)(1 << 6),
    USB_CDC_BREAK_TX = (uint32_t)(1 << 7),

    USB_ALL_ISR_EVENTS = (uint32_t)(USB_MOUNT | USB_UMOUNT | USB_SUSPEND | USB_RESUME | USB_HID_CPLT_TX | USB_CDC_RX | USB_CDC_CPLT_TX | USB_CDC_BREAK_TX)
};

enum COMPOSITE_USB_EVENTS
{
    USB_HID_EMPTY = (uint32_t)(1 << 8),
    USB_CDC_EMPTY = (uint32_t)(1 << 9),
    USB_ALL_EVENTS = (uint32_t)(USB_ALL_ISR_EVENTS | USB_HID_EMPTY | USB_CDC_EMPTY)
};
#endif //__usb_events_h__