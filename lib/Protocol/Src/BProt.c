#include "BProtConf.h"
#include "BProt.h"

#if defined(USE_RTOS)
TaskHandle_t BPHandle = NULL;
QueueHandle_t BPQueue = NULL;
#endif

void BProtThread(void *arg);
void BPSlaveHandler(uint8_t *data, uint16_t size);
int BPCheckHead(BPFrame_t *frame, uint16_t size);
int BPCheckData(BPFrame_t *frame);

void BPDataHandler(BPFrame_t *frame);
void BPGenMsg(BPmsgTypeConf_t *MsgConf, BPFrame_t *frame);
uint16_t BPCalkLen(BPFrame_t *frame);

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
        BPErrHandler();
        break;
    }
}

void BPSlaveHandler(uint8_t *data, uint16_t size)
{
    BPHead_t *head = (BPHead_t *)(void *)data;
    BPFrame_t frame = {head, NULL, NULL};
    BPmsgTypeConf_t MsgConf = {0};
    MsgConf.BPMode = SLAVE_MODE;
    if (size < sizeof(*frame.head))
    {
        return;
    }
    if (BPCheckHead(&frame, size))
    {
        return;
    }
    if (BPCheckData(&frame))
    {
        BPErrHandler();
        return;
    }
    BPDataHandler(&frame);
    BPGenMsg(&MsgConf, &frame);
}

void BPErrHandler(void)
{
#if defined(VRS_ERRORS_COUNT)
    VAL(VRS_ERRORS_COUNT)
    ++;
#endif
}

int BPCheckHead(BPFrame_t *frame, uint16_t size)
{
    uint8_t *tmp = (uint8_t *)frame->head;
    BPHead_t *head = frame->head;
    while (head->crc != crc16(tmp,
                              (sizeof(*head) - sizeof(head->crc))))
    {
        tmp++;
        head = (BPHead_t *)(void *)tmp;
        size--;
        if (size < sizeof(*head))
        {
            return -1;
        }
    }
    if (head->dest != MY_ADDRESS)
    {
        return -1;
    }
    frame->head = head;
    frame->data = (uint32_t *)(void *)(tmp + sizeof(*head));
    frame->xor = (uint32_t *)(void *)(tmp + head->len + sizeof(*head));
    return 0;
}

int BPCheckData(BPFrame_t *frame)
{
    if (*frame->xor != xor32(frame->data,
                             frame->head->len / sizeof(uint32_t)))
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
        for (uint16_t addr = 0, reg = 1; addr < (frame->head->len / sizeof(uint32_t)); addr += 2, reg += 2)
        {
            if (VRSetData(&frame->data[addr], &frame->data[reg]))
            {
                BPErrHandler();
            }
        }

        break;
    case RANDOM_WRITE_ANSW:
        /* code */
        break;
    case RANDOM_READ_COMM:
        for (uint16_t addr = 0, reg = 1; addr < (frame->head->len / sizeof(uint32_t)); addr += 2, reg += 2)
        {
            if (VRGetData(&frame->data[addr], &frame->data[reg]))
            {
                BPErrHandler();
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
        BPErrHandler();
        break;
    }
}

void BPGenMsg(BPmsgTypeConf_t *MsgConf, BPFrame_t *frame)
{
    uint8_t *tmp = (uint8_t *)frame->head;
    switch (MsgConf->BPMode)
    {
    case MASTER_MODE:
        /* code */
        break;
    case SLAVE_MODE:
        SWAP(frame->head->dest, frame->head->source);
        frame->head->len = BPCalkLen(frame);
        frame->head->type++;
        frame->head->tag++;
        frame->head->crc = crc16((uint8_t *)frame->head, (sizeof(*frame->head) -
                                                          sizeof(frame->head->crc)));
        frame->xor = (uint32_t *)(void *)(tmp +
                                          frame->head->len +
                                          sizeof(*frame->head));
        *frame->xor = xor32(frame->data,
                            frame->head->len / sizeof(uint32_t));
        break;
    case TRANSIT_MODE:
        /* code */
        break;

    default:
        break;
    }
    BPTransmitCallBack((uint8_t *)frame->head, (sizeof(*frame->head) +
                                                frame->head->len + sizeof(*frame->xor)));
}

uint16_t BPCalkLen(BPFrame_t *frame)
{
    uint16_t len = 0;
    switch (frame->head->type)
    {
    case RANDOM_WRITE_ANSW:
        /* code */
        break;
    case RANDOM_READ_COMM:
        len = frame->head->len;
        break;
    case RANDOM_READ_ANSW:
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
        break;
    }
    return len;
}
