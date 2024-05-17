#include "BPCDCport.h"

void CdcRecievCallBack(uint8_t *data, uint16_t size)
{
    BPBuf_t Buf = {0};
    if (size > BP_CONF_MAX_LEN_MSG)
    {
        return;
    }

    memcpy(Buf.data, data, size);
    Buf.MsgConf.BPMode = SLAVE_MODE;
    Buf.size = size;
    xQueueSend(BPQueue, &Buf, 10);
}