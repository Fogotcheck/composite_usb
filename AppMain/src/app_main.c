#include "app_main.h"
#ifdef USE_RTOS
#include "FreeRTOS.h"
#include "task.h"
void MainThread(void *arg);
#endif
uint32_t Data[32] = {0};

int ReadTestHandlers(uint32_t *arg);
void ErrTestHandlers(uint32_t *arg);
int WriteTestHandlers(uint32_t *arg);

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

    BPHandlersType_t Handle = {0};
    Handle.Get = ReadTestHandlers;
    Handle.Set = WriteTestHandlers;
    Handle.Err = ErrTestHandlers;
    uint32_t addr = VRS_VERSION;
    for (uint16_t i = 0; i < sizeof(Data) / sizeof(Data[0]); i++)
    {
        BPSetHandler(addr, &Handle);
        addr += sizeof(uint32_t);
    }

    vTaskDelay(1000);
    // Test();
    D_INIT_INFO;
    while (1)
    {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        vTaskDelay(100);
    }
}

int ReadTestHandlers(uint32_t *arg)
{

    printf("Read::\t%lx\r\n", *arg);
    return 0;
}

void ErrTestHandlers(uint32_t *arg)
{

    printf("Err::\t%lx\r\n", *arg);
}

int WriteTestHandlers(uint32_t *arg)
{
    if (*arg == 4)
    {
        printf("err\r\n");
        return -1;
    }

    printf("Write::\t%lx\r\n", *arg);
    return 0;
}