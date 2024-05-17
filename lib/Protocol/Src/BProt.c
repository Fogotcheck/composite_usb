#include "BProtConf.h"
#include "BProt.h"

#if defined(USE_RTOS)
TaskHandle_t BPHandle = NULL;
QueueHandle_t BPQueue = NULL;
#endif

void BProtThread(void *arg);
void BPSlaveHandler(uint8_t *data, uint16_t size);
int BPCheckHead(BPHead_t *head);
int BPCheckData(BPFrame_t *frame);

int BProtInit(void *PtrRegMap, uint16_t MapSize)
{
    if (VRMapInit(PtrRegMap, MapSize))
    {
        return -1;
    }
    int ret = 0;
#if defined(USE_RTOS)
    ret = xTaskCreate(BProtThread, "BProtThread",
                      BPROT_THR_STACK, NULL,
                      BPROT_THR_PRIORITY, &BPHandle);
    ret = ret == pdPASS ? 0 : -1;

#endif

    return ret;
}

#if defined(USE_RTOS)
void BProtThread(__attribute__((unused)) void *arg)
{
    BPBuf_t Buf;
    BPQueue = xQueueCreate(2, sizeof(Buf));
    if (BPQueue == NULL)
    {
        vTaskDelete(NULL);
    }

    while (1)
    {
        xQueueReceive(BPQueue, &Buf, portMAX_DELAY);
        BProtMsgHandler(&Buf);
    }
}
#endif

void BProtMsgHandler(BPBuf_t *Buf)
{
    switch (Buf->MsgConf.BPMode)
    {
    case MASTER_MODE:
        /* code */
        break;
    case SLAVE_MODE:
        BPSlaveHandler(Buf->data, Buf->size);
        break;
    case TRANSIT_MODE:
        /* code */
        break;

    default:
#if defined(VRS_ERRORS_COUNT)
        VAL(VRS_ERRORS_COUNT)
        ++;
#endif
        break;
    }
}

void BPSlaveHandler(uint8_t *data, uint16_t size)
{
    BPHead_t *head = (BPHead_t *)(void *)data;
    BPFrame_t frame = {head,
                       (uint32_t *)(void *)(data + sizeof(*head)),
                       (uint32_t *)(void *)(data + head->len + sizeof(*head))};
    if (size < (sizeof(*frame.head) + frame.head->len + sizeof(*frame.xor)))
    {
        return;
    }
    if (BPCheckHead(frame.head))
    {
        return;
    }
    if (BPCheckData(&frame))
    {
#if defined(VRS_ERRORS_COUNT)
        VAL(VRS_ERRORS_COUNT)
        ++;
#endif
        return;
    }
}

int BPCheckHead(BPHead_t *head)
{
    if (head->crc != crc16((uint8_t *)head, sizeof(*head)))
    {
        return -1;
    }
    if (head->dest != MY_ADDRESS)
    {
        return -1;
    }

    return 0;
}

int BPCheckData(BPFrame_t *frame)
{
    if (*frame->xor != xor32(frame->data, frame->head->len / sizeof(uint32_t)))
    {
        return -1;
    }

    return 0;
}

void BPDataHandler(BPFrame_t *frame)
{
    switch (frame->head->type)
    {
    case RANDOM_WRITE_COMM:
        for (uint16_t i = 0, j = 1; i < (frame->head->len / sizeof(uint32_t)); i++, j++)
        {
            if (VRSetData(&frame->data[i], &frame->data[j]))
            {
            }
        }

        break;
    case RANDOM_WRITE_ANSW:
        /* code */
        break;
    case RANDOM_READ_COMM:
        for (uint16_t i = 0, j = 1; i < (frame->head->len / sizeof(uint32_t)); i++, j++)
        {
            if (VRGetData(&frame->data[i], &frame->data[j]))
            {
            }
        }
        break;
    case RANDOM_READ_ANSW:
        /* code */
        break;
    case BLOCK_WRITE_COMM:
        /* code */
        break;
    case BLOCK_WRITE_ANSW:
        /* code */
        break;
    case BLOCK_READ_COMM:
        /* code */
        break;
    case BLOCK_READ_ANSW:
        /* code */
        break;
    default:
#if defined(VRS_ERRORS_COUNT)
        VAL(VRS_ERRORS_COUNT)
        ++;
#endif
        break;
    }
}