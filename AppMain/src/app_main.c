#include "app_main.h"
#ifdef USE_RTOS
#include "FreeRTOS.h"
#include "task.h"
void MainThread(void *arg);
#endif
uint32_t Data[32] = {0};
void AppMain(void)
{
    DebugPrintSwitch(DEBUG_PRINT_ENABLE);
#ifdef USE_RTOS
    BaseType_t ret = xTaskCreate(MainThread, "MainTask", 512, NULL,
                                 1, NULL);
    if (ret != pdPASS)
    {
        Error_Handler();
    }
    vTaskStartScheduler();
#else
    MainThread((void *)NULL);
#endif
}

void MainThread(__attribute__((unused)) void *arg)
{

    if (CompositeUsbInit())
    {
        D_ERR_MSG_L0;
        Error_Handler();
    }
     vTaskDelay(100);
    if (BProtInit((void *)Data, sizeof(Data)))
    {
        D_ERR_MSG_L0;
    }

    vTaskDelay(1000);
    Test();
    D_INIT_INFO;
    while (1)
    {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        vTaskDelay(100);
    }
}