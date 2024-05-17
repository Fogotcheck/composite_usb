#ifndef __BProtDef_h__
#define __BProtDef_h__

#define SWAP(a, b) \
    {              \
        a ^= b;    \
        b ^= a;    \
        a ^= b;    \
    }

enum BPMode
{
    MASTER_MODE,
    SLAVE_MODE,
    TRANSIT_MODE,
};

enum BPTypeMess
{
    RANDOM_WRITE_COMM = 3,
    RANDOM_WRITE_ANSW = 4,
    RANDOM_READ_COMM = 5,
    RANDOM_READ_ANSW = 6,
    BLOCK_WRITE_COMM = 7,
    BLOCK_WRITE_ANSW = 8,
    BLOCK_READ_COMM = 9,
    BLOCK_READ_ANSW = 10,
};

#endif //__BProtDef_h__