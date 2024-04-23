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
    // static char VComPortBufTx[] = "Hello cdc\r\n";
   
    while (1)
    {
       
    }
}