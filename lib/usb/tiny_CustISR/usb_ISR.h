#ifndef __usb_ISR_h__
#define __usb_ISR_h__
#include "tusb.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "usb_events.h"

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len);
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);
#endif //__usb_ISR_h__