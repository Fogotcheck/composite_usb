#include "VirtComPort.h"

TaskHandle_t VComPortHandle = NULL;
TaskHandle_t MouseHandle = NULL;
TaskHandle_t CompositeHandle = NULL;

extern USBD_HandleTypeDef hUsbDeviceFS;

void VirtComPortThread(void *arg);
void MouseThread(void *arg);
void CompositeThread(void *arg);

int VirtComPortInit(void)
{
    // BaseType_t ret = xTaskCreate(VirtComPortThread, "VComPortTask", 512, NULL,
    //                              2, &VComPortHandle);
    // BaseType_t ret = xTaskCreate(MouseThread, "MouseTask", 512, NULL,
    //                              2, &MouseHandle);
    BaseType_t ret = xTaskCreate(CompositeThread, "CompositeTask", 512, NULL,
                                 2, &CompositeHandle);
    return ret == pdPASS ? 0 : -1;
}

// void VirtComPortThread(__attribute__((unused)) void *arg)
// {
//     static char VComPortBufTx[] = "Hello cdc\r\n";
//     MX_USB_Device_Init();
//     while (1)
//     {
//         CDC_Transmit_FS((unsigned char *)VComPortBufTx, strlen(VComPortBufTx));
//         vTaskDelay(1000);
//     }
// }

// void MouseThread(__attribute__((unused)) void *arg)
// {
//     static uint8_t MouseReport[] = {0, 100, 0, 0};
//     MX_USB_Device_Init();
//     while (1)
//     {
//         USBD_HID_SendReport(&hUsbDeviceFS, MouseReport, sizeof(MouseReport));
//         vTaskDelay(1000);
//     }
// }

void CompositeThread(__attribute__((unused)) void *arg)
{
    static char VComPortBufTx[] = "Hello cdc\r\n";
    static uint8_t MouseReport[] = {0, 100, 0, 0};
    MX_USB_Device_Init();
    while (1)
    {
        CDC_Transmit_FS((unsigned char *)VComPortBufTx, strlen(VComPortBufTx));
        vTaskDelay(1000);
        USBD_HID_SendReport(&hUsbDeviceFS, MouseReport, sizeof(MouseReport), HID_InstID);
        vTaskDelay(1000);
    }
}