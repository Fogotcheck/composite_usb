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

int CompositeUsbInit(void)
{
  BaseType_t ret = xTaskCreate(UsbMainThread, "UsbMainTask", 512, NULL,
                               2, &UsbMainHandle);

  return ret == pdPASS ? 0 : -1;
}

void UsbMainThread(__attribute__((unused)) void *arg)
{

  HAL_PWREx_EnableVddUSB();
  __HAL_RCC_USB_CLK_ENABLE();
  printf("tusb::\t%hhu\r\n", tud_init(BOARD_TUD_RHPORT));
  BaseType_t ret = 0;
  ret = xTaskCreate(UsbCdcThread, "UsbCdcTask", 512, NULL,
                    2, &UsbCdcHandle);
  if (ret != pdPASS)
  {
    printf("Cdc thr err\r\n");
  }

  // ret = xTaskCreate(UsbHidThread, "UsbHidTask", 512, NULL,
  //                   2, &UsbHidHandle);
  // if (ret != pdPASS)
  // {
  //   printf("Hid thr err\r\n");
  // }
  printf("Composite usb::\tinit\r\n");
  while (1)
  {
    tud_task(); // device task

    vTaskDelay(3);
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
      /* code */
      break;

    default:
      break;
    }

    vTaskDelay(1000);
  }
}
void UsbHidThread(__attribute__((unused)) void *arg)
{
  while (1)
  {
    /* code */
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