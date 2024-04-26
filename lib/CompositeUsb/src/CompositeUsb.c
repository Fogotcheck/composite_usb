#include "CompositeUsb.h"
#include "tusb.h"

TaskHandle_t UsbMainHandle = NULL;
TimerHandle_t UsbTudTimer = NULL;
EventGroupHandle_t UsbISREvents = NULL;
EventGroupHandle_t InterfaceEvents = NULL;
TaskHandle_t UsbCdcHandle = NULL;
TaskHandle_t UsbHidHandle = NULL;
QueueHandle_t UsbCdcQueue = NULL;
QueueHandle_t UsbHidQueue = NULL;

void UsbMainThread(void *arg);
void UsbCdcThread(void *arg);
void UsbHidThread(void *arg);
void USB_HP_IRQHandler(void);
void USB_LP_IRQHandler(void);
void UsbTudCallback(TimerHandle_t xTimer);
void UsbEventsHandler(EventBits_t Events);

void BtnTest(uint32_t *btn);

int CompositeUsbInit(void)
{
  BaseType_t ret = 0;
  HAL_PWREx_EnableVddUSB();
  __HAL_RCC_USB_CLK_ENABLE();
  tud_init(BOARD_TUD_RHPORT);

  UsbTudTimer = xTimerCreate("tud_timer", pdMS_TO_TICKS(USB_BINTERVAL_MS), pdTRUE, NULL, UsbTudCallback);
  if (UsbTudTimer == NULL)
  {
    return -1;
  }
  do
  {
    ret = xTimerStart(UsbTudTimer, 0);
    if (ret == pdFAIL)
    {
      printf("tud timer err,or sheduler don't start\r\n");
    }
  } while (ret != pdPASS);
  ret = xTaskCreate(UsbMainThread, "UsbMainTask", 512, NULL,
                    USB_THREAD_PRIORITY, &UsbMainHandle);
  if (ret != pdPASS)
  {
    return -1;
  }

  return 0;
}

void UsbMainThread(__attribute__((unused)) void *arg)
{
  BaseType_t ret = 0;
  EventBits_t Event = 0;
  EventBits_t Mask = 1;

  UsbISREvents = xEventGroupCreate();
  if (UsbISREvents == NULL)
  {
    printf("Usb ISR events::err\r\n");
  }

  InterfaceEvents = xEventGroupCreate();
  if (InterfaceEvents == NULL)
  {
    printf("Usb ISR events::err\r\n");
  }

  if (UsbISREvents == NULL)
  {
    do
    {
      printf("UsbEvents err\r\n");
    } while (1);
  }
  ret = xTaskCreate(UsbCdcThread, "UsbCdcTask", 512, NULL,
                    (USB_THREAD_PRIORITY), &UsbCdcHandle);
  if (ret != pdPASS)
  {
    printf("Cdc thr err\r\n");
  }
  vTaskSuspend(UsbCdcHandle);
  ret = xTaskCreate(UsbHidThread, "UsbHidTask", 512, NULL,
                    (USB_THREAD_PRIORITY), &UsbHidHandle);
  if (ret != pdPASS)
  {
    printf("Hid thr err\r\n");
  }
  vTaskSuspend(UsbHidHandle);
  printf("Composite usb::\tinit\r\n");
  while (1)
  {
    Event = xEventGroupWaitBits(UsbISREvents, USB_ALL_ISR_EVENTS, pdFALSE, pdFALSE, portMAX_DELAY);
    for (uint8_t i = 0; i < FREERTOS_MAX_EVENT_SIZE; i++)
    {
      if (Mask & Event)
      {
        UsbEventsHandler(Mask & Event);
      }

      Mask <<= 1;
    }
    Mask = 1;
  }
}

void UsbCdcThread(__attribute__((unused)) void *arg)
{

  UsbCdcQueue = xQueueCreate(USB_CDC_QUEUE_LEN, sizeof(CdcReport_t));
  if (UsbCdcQueue == NULL)
  {
    printf("cdc queue err\r\n");
  }

  EventBits_t Event = 0;
  CdcReport_t Buf = {0};
  while (1)
  {
    xQueueReceive(UsbCdcQueue, &Buf, portMAX_DELAY);
    switch (Buf.DType)
    {
    case CDC_TX:
      tud_cdc_n_write(0, Buf.Data, Buf.Size);
      tud_cdc_n_write_flush(0);
      Event = xEventGroupWaitBits(InterfaceEvents, USB_CDC_EMPTY, pdFALSE, pdTRUE, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS));
      if ((Event & USB_CDC_EMPTY) == 0)
      {
        printf("cdc tx timeout\r\n");
      }
      xEventGroupClearBits(InterfaceEvents, USB_CDC_EMPTY);
      break;
    case CDC_RX:
    {
      char tmp[] = "reciev::\t";
      if (UsbCdcTransmit((uint8_t *)tmp, sizeof(tmp)))
      {
        printf("Transmit cdc pref err\r\n");
      }
      if (UsbCdcTransmit(Buf.Data, Buf.Size))
      {
        printf("Transmit cdc data err\r\n");
      }
      static HIDReport_t TmpHid = {0};
      BtnTest(&TmpHid.Buttons);
      if (UsbHidTransmit((uint8_t *)&TmpHid, sizeof(TmpHid)))
      {
        printf("Transmit hid data err\r\n");
      }

      break;
    }
    default:
      break;
    }
  }
}

int UsbCdcTransmit(uint8_t *Data, uint32_t Len)
{
  CdcReport_t Buf = {0};
  BaseType_t ret = 0;
  if (Len > (uint32_t)sizeof(Buf.Data))
  {
    return -1;
  }
  memcpy(Buf.Data, Data, Len);
  Buf.Size = Len;
  ret = xQueueSend(UsbCdcQueue, &Buf, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS));
  return ret == pdTRUE ? 0 : -1;
}

void UsbHidThread(__attribute__((unused)) void *arg)
{
  EventBits_t Event = 0;
  HIDReport_t Report = {0};

  UsbHidQueue = xQueueCreate(USB_CDC_QUEUE_LEN, sizeof(HIDReport_t));
  if (UsbHidQueue == NULL)
  {
    printf("hid queue err\r\n");
  }

  while (1)
  {
    xQueueReceive(UsbHidQueue, (void *)&Report, portMAX_DELAY);
    while (!tud_hid_ready())
    {
      printf("hid not ready\r\n");
    }

    tud_hid_report(0, &Report, sizeof(Report));
    Event = xEventGroupWaitBits(InterfaceEvents, USB_HID_EMPTY, pdFALSE, pdTRUE, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS));
    if ((Event & USB_HID_EMPTY) == 0)
    {
      printf("hid tx timeout\r\n");
    }
    xEventGroupClearBits(InterfaceEvents, USB_HID_EMPTY);
  }
}

int UsbHidTransmit(uint8_t *Data, uint32_t Len)
{
  HIDReport_t Report = {0};
  BaseType_t ret = 0;
  if (Len != sizeof(HIDReport_t))
  {
    return -1;
  }
  memcpy(&Report, Data, Len);
  ret = xQueueSend(UsbHidQueue, &Report, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS));
  return ret == pdTRUE ? 0 : -1;
}

void UsbTudCallback(TimerHandle_t xTimer)
{
  if (xTimer == UsbTudTimer)
  {
    tud_task(); // device task
  }
}

void UsbEventsHandler(EventBits_t Events)
{
  CdcReport_t Buf = {0};
  Buf.DType = CDC_RX;

  if (Events & USB_ALL_ISR_EVENTS)
  {
    xEventGroupClearBits(UsbISREvents, Events);
  }

  switch (Events)
  {
  case USB_MOUNT:
    vTaskResume(UsbCdcHandle);
    vTaskResume(UsbHidHandle);
    break;
  case USB_UMOUNT:
    vTaskSuspend(UsbCdcHandle);
    vTaskSuspend(UsbHidHandle);
    break;
  case USB_SUSPEND:
    vTaskSuspend(UsbCdcHandle);
    vTaskSuspend(UsbHidHandle);
    break;
  case USB_RESUME:
    vTaskResume(UsbCdcHandle);
    vTaskResume(UsbHidHandle);
    break;
  case USB_HID_CPLT_TX:
    xEventGroupSetBits(InterfaceEvents, USB_HID_EMPTY);
    break;
  case USB_CDC_RX:
    if (tud_cdc_n_available(0))
    {
      Buf.Size = tud_cdc_n_read(0, Buf.Data, sizeof(Buf.Data));
      if (xQueueSend(UsbCdcQueue, &Buf, 5) != pdPASS)
      {
        printf("Cdc RX err\r\n");
      }
    }
    break;
  case USB_CDC_CPLT_TX:
    xEventGroupSetBits(InterfaceEvents, USB_CDC_EMPTY);
    break;
  case USB_CDC_BREAK_TX:
    printf("cdc tx break\r\n");
    xEventGroupSetBits(InterfaceEvents, USB_CDC_EMPTY);
    break;
  default:
    break;
  }
}

void BtnTest(uint32_t *btn)
{
  static uint8_t state = 0;
  static uint32_t mask = 1;
  switch (state)
  {
  case 0:
    if (*btn >= 0xfffff)
    {
      mask = 1;
      state++;
      break;
    }
    *btn |= mask;
    mask <<= 1;
    break;
  case 1:
    if (*btn == 0)
    {
      mask = 1;
      state++;
      break;
    }
    *btn &= ~mask;
    mask <<= 1;
    break;
  default:
    state = 0;
    break;
  }
}
