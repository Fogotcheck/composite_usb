#include "app_main.h"
#ifdef USE_RTOS
#include "FreeRTOS.h"
#include "task.h"
void MainThread(void *arg);
#endif

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
        Error_Handler();
    }
    printf("%s::\tinit end\r\n",__FUNCTION__ );
    while (1)
    {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        vTaskDelay(100);
    }
}