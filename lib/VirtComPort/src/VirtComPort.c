#include "VirtComPort.h"

TaskHandle_t VComPortHandle = NULL;

void VirtComPortThread(void *arg);

int VirtComPortInit(void)
{
    BaseType_t ret = xTaskCreate(VirtComPortThread, "VComPortTask", 512, NULL,
                                 2, &VComPortHandle);

    return ret == pdPASS ? 0 : -1;
}

void VirtComPortThread(__attribute__((unused)) void *arg)
{
    static char VComPortBufTx[] = "Hello cdc\r\n";
    MX_USB_Device_Init();
    while (1)
    {
        CDC_Transmit_FS((unsigned char *)VComPortBufTx, strlen(VComPortBufTx));
        vTaskDelay(1000);
    }
}