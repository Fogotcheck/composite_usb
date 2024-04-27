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
void UsbEventsHandler(EventBits_t Events);

void BtnTest(uint32_t *btn);

int CompositeUsbInit(void)
{
  BaseType_t ret = 0;
  ret = xTaskCreate(UsbMainThread, "UsbMainTask", USB_MAIN_THR_STACK, NULL,
                    (configMAX_PRIORITIES - 1), &UsbMainHandle);
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
  InterfaceEvents = xEventGroupCreate();
  if (InterfaceEvents == NULL)
  {
    D_ERR_MSG_L1;
  }

  if (UsbISREvents == NULL)
  {
    do
    {
      D_ERR_MSG_L0;
    } while (1);
  }
  ret = xTaskCreate(UsbCdcThread, "UsbCdcTask", USB_CDC_THR_STACK, NULL,
                    (USB_THREAD_PRIORITY), &UsbCdcHandle);
  if (ret != pdPASS)
  {
    D_ERR_MSG_L1;
  }
  vTaskSuspend(UsbCdcHandle);
  ret = xTaskCreate(UsbHidThread, "UsbHidTask", USB_HID_THR_STACK, NULL,
                    (USB_THREAD_PRIORITY), &UsbHidHandle);
  if (ret != pdPASS)
  {
    D_ERR_MSG_L1;
  }
  vTaskSuspend(UsbHidHandle);

  HAL_PWREx_EnableVddUSB();
  __HAL_RCC_USB_CLK_ENABLE();

  // init device stack on configured roothub port
  // This should be called after scheduler/kernel is started.
  // Otherwise it could cause kernel issue since USB IRQ handler does use RTOS queue API.
  tud_init(BOARD_TUD_RHPORT);

  D_INIT_INFO;
  while (1)
  {
    // put this thread to waiting state until there is new events
    tud_task(); // device task
    Event = xEventGroupWaitBits(UsbISREvents, USB_ALL_ISR_EVENTS, pdFALSE, pdFALSE, pdMS_TO_TICKS(USB_BINTERVAL_MS));
    if (Event)
    {
      for (uint8_t i = 0; i < FREERTOS_MAX_EVENT_SIZE; i++)
      {
        if (Mask & Event)
        {
          UsbEventsHandler(Mask & Event);
        }

        Mask <<= 1;
      }
    }
    Mask = 1;
  }
}

void UsbCdcThread(__attribute__((unused)) void *arg)
{
  EventBits_t Event = 0;
  CdcReport_t Buf = {0};
  UsbCdcQueue = xQueueCreate(USB_CDC_QUEUE_LEN, sizeof(CdcReport_t));
  if (UsbCdcQueue == NULL)
  {
    D_ERR_MSG_L1;
  }
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
        D_TIMEOUT_MSG;
      }
      xEventGroupClearBits(InterfaceEvents, USB_CDC_EMPTY);
      break;
    case CDC_RX:
    {
      /* echo mode + hid test */
      char TmpCdc[] = "\nreciev::\t";
      if (UsbCdcTransmit((uint8_t *)TmpCdc, sizeof(TmpCdc)))
      {
        D_ERR_MSG_L1;
      }
      if (UsbCdcTransmit(Buf.Data, Buf.Size))
      {
        D_ERR_MSG_L1;
      }

      static HIDReport_t TmpHid = {0};
      BtnTest(&TmpHid.Buttons);
      if (UsbHidTransmit((uint8_t *)&TmpHid, sizeof(TmpHid)))
      {
        D_ERR_MSG_L1;
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
    D_ERR_MSG_L1;
  }
  while (1)
  {
    xQueueReceive(UsbHidQueue, (void *)&Report, portMAX_DELAY);
    while (!tud_hid_ready())
    {
      D_ERR_MSG_L1;
    }

    tud_hid_report(0, &Report, sizeof(Report));
    Event = xEventGroupWaitBits(InterfaceEvents, USB_HID_EMPTY, pdFALSE, pdTRUE, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS));
    if ((Event & USB_HID_EMPTY) == 0)
    {
      D_TIMEOUT_MSG;
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
      if (xQueueSend(UsbCdcQueue, &Buf, pdMS_TO_TICKS(USB_WAIT_EVENT_TIME_MS)) != pdPASS)
      {
        D_ERR_MSG_L1;
      }
    }
    break;
  case USB_CDC_CPLT_TX:
    xEventGroupSetBits(InterfaceEvents, USB_CDC_EMPTY);
    break;
  case USB_CDC_BREAK_TX:
    D_ERR_MSG_L1;
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
