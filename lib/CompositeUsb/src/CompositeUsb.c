#include "CompositeUsb.h"
#include "tusb.h"

TaskHandle_t UsbMainHandle = NULL;
TaskHandle_t UsbCdcHandle = NULL;
TaskHandle_t UsbHidHandle = NULL;
QueueHandle_t UsbCdcQueue = NULL;
QueueHandle_t UsbHidQueue = NULL;

void UsbMainThread(void *arg);
void UsbCdcThread(void *arg);
void UsbHidThread(void *arg);
void USB_HP_IRQHandler(void);
void USB_LP_IRQHandler(void);

void BtnTest(uint32_t *btn);

int CompositeUsbInit(void)
{
  BaseType_t ret = xTaskCreate(UsbMainThread, "UsbMainTask", 512, NULL,
                               2, &UsbMainHandle);

  return ret == pdPASS ? 0 : -1;
}

void UsbMainThread(__attribute__((unused)) void *arg)
{
  CdcReport_t Buf = {0};
  Buf.DType = CDC_RX;
  BaseType_t ret = 0;

  HAL_PWREx_EnableVddUSB();
  __HAL_RCC_USB_CLK_ENABLE();
  printf("tusb::\t%hhu\r\n", tud_init(BOARD_TUD_RHPORT));

  ret = xTaskCreate(UsbCdcThread, "UsbCdcTask", 512, NULL,
                    2, &UsbCdcHandle);
  if (ret != pdPASS)
  {
    printf("Cdc thr err\r\n");
  }

  ret = xTaskCreate(UsbHidThread, "UsbHidTask", 512, NULL,
                    2, &UsbHidHandle);
  if (ret != pdPASS)
  {
    printf("Hid thr err\r\n");
  }
  printf("Composite usb::\tinit\r\n");
  while (1)
  {
    tud_task(); // device task
    if (tud_cdc_n_available(0))
    {
      Buf.Size = tud_cdc_n_read(0, Buf.Data, sizeof(Buf.Data));
      if (xQueueSend(UsbCdcQueue, &Buf, 5) != pdPASS)
      {
        printf("Cdc RX err\r\n");
      }
    }

    vTaskDelay(5);
  }
}

void UsbCdcThread(__attribute__((unused)) void *arg)
{
  UsbCdcQueue = xQueueCreate(USB_CDC_QUEUE_LEN, sizeof(CdcReport_t));
  CdcReport_t Buf = {0};
  while (1)
  {
    xQueueReceive(UsbCdcQueue, &Buf, portMAX_DELAY);
    switch (Buf.DType)
    {
    case CDC_TX:
      tud_cdc_n_write(0, Buf.Data, Buf.Size);
      tud_cdc_n_write_flush(0);
      break;
    case CDC_RX:
    {
      char tmp[] = "reciev::\t";
      tud_cdc_n_write(0, tmp, sizeof(tmp));
      tud_cdc_n_write(0, Buf.Data, Buf.Size);
      tud_cdc_n_write_flush(0);
      break;
    }
    default:
      break;
    }
  }
}

void UsbHidThread(__attribute__((unused)) void *arg)
{
  UsbHidQueue = xQueueCreate(USB_CDC_QUEUE_LEN, sizeof(CdcReport_t));
  HIDReport_t report = {0};
  while (1)
  {

    if (!tud_hid_ready())
    {
      continue;
    }
    BtnTest(&report.Buttons);
    tud_hid_report(0, &report, sizeof(report));
    vTaskDelay(10);
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