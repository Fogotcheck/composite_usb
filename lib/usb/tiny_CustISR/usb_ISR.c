#include "usb_ISR.h"

extern EventGroupHandle_t UsbEvents;
//--------------------------------------------------------------------+
// Forward USB interrupt events to TinyUSB IRQ Handler
//--------------------------------------------------------------------+
void USB_HP_IRQHandler(void)
{
    tud_int_handler(0);
}

void USB_LP_IRQHandler(void)
{
    tud_int_handler(0);
}

// Invoked when device is mounted
void tud_mount_cb(void)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_MOUNT, &pxHigherPriorityTaskWoken);
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_UMOUNT, &pxHigherPriorityTaskWoken);
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_SUSPEND, &pxHigherPriorityTaskWoken);
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_RESUME, &pxHigherPriorityTaskWoken);
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;
    (void)len;
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_HID_CPLT_TX, &pxHigherPriorityTaskWoken);
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;
}
// Invoked when received new data
void tud_cdc_rx_cb(uint8_t itf)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_CDC_RX, &pxHigherPriorityTaskWoken);
}
// Invoked when a TX is complete and therefore space becomes available in TX buffer
void tud_cdc_tx_complete_cb(uint8_t itf)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_CDC_CPLT_TX, &pxHigherPriorityTaskWoken);
}
// Invoked when received send break
void tud_cdc_send_break_cb(uint8_t itf, uint16_t duration_ms)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(UsbEvents, USB_CDC_BREAK_TX, &pxHigherPriorityTaskWoken);
}
