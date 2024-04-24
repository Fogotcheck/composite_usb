#include "VirtComPort.h"
#include "tusb.h"
#include "stm32wb55xx.h"
#include "stm32wbxx_hal.h"
TaskHandle_t VComPortHandle = NULL;

void VirtComPortThread(void *arg);
void USB_HP_IRQHandler(void);
void USB_LP_IRQHandler(void);

int VirtComPortInit(void)
{
    BaseType_t ret = xTaskCreate(VirtComPortThread, "VComPortTask", 512, NULL,
                                 2, &VComPortHandle);

    return ret == pdPASS ? 0 : -1;
}

void VirtComPortThread(__attribute__((unused)) void *arg)
{
    static char VComPortBufTx[] = "Hello cdc\r\n";
    HAL_PWREx_EnableVddUSB();
    __HAL_RCC_USB_CLK_ENABLE();
    printf("tusb::\t%hhu\r\n", tud_init(BOARD_TUD_RHPORT));

    while (1)
    {
        tud_task(); // device task
        // for (size_t i = 0; i < sizeof(VComPortBufTx); i++)
        // {
        //     tud_cdc_n_write_char(0, VComPortBufTx[i]);
        // }

        // tud_cdc_n_write_flush(0);
         vTaskDelay(3);
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