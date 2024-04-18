#include "app_main.h"
#ifdef USE_RTOS
#include "FreeRTOS.h"
#include "task.h"
void MainThread(void *arg);
#endif

void AppMain(void)
{
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
    while (1)
    {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        vTaskDelay(100);
    }
}