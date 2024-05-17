#include "VReg.h"

VRegData_t VRMap = {0};

int sscanf_custom(const char *str, const char *format, ...);
int vsscanf_custom(const char *str, const char *format, va_list args);
void SetCompileTime(char *t, char *d);

int VRGetData(uint32_t *addr, uint32_t *data)
{
    if (!VREG_GOOD_ADDR(*addr))
    {
        return -1;
    }
    *data = VAL(*addr);

    return 0;
}

int VRSetData(uint32_t *addr, uint32_t *data)
{
    if (!VREG_GOOD_ADDR(*addr))
    {
        return -1;
    }
    VAL(*addr) = *data;
    return 0;
}

int VRMapInit(void *PtrRegMap, uint16_t MapSize)
{
    if ((PtrRegMap == NULL) || (MapSize == 0))
    {
        return -1;
    }

    VRMap.mem = PtrRegMap;
    VRMap.size = MapSize;
#if defined(BP_CONF_SYSTEM_REGS_EN)
    VAL(VRS_ERRORS_COUNT) = 0;
    VAL(VRS_MEMORY_SIZE) = MapSize;
    SetCompileTime(__TIME__, __DATE__);
#endif
    return 0;
}

void SetCompileTime(char *t, char *d)
{
#define __MONTH__(date)                                                                                \
    (date[2] == 'n' ? (date[1] == 'a' ? "01" : "06") : date[2] == 'b' ? "02"                           \
                                                   : date[2] == 'r'   ? (date[0] == 'M' ? "03" : "04") \
                                                   : date[2] == 'y'   ? "05"                           \
                                                   : date[2] == 'l'   ? "07"                           \
                                                   : date[2] == 'g'   ? "08"                           \
                                                   : date[2] == 'p'   ? "09"                           \
                                                   : date[2] == 't'   ? "10"                           \
                                                   : date[2] == 'v'   ? "11"                           \
                                                                      : "12")

    char day[3], month[3], year[3], hour[3];
    int DayNum, MonthNum, YearNum, HourNum;

    // "10"
    hour[0] = t[0];
    hour[1] = t[1];
    hour[2] = 0;

    day[0] = d[4];
    day[1] = d[5];
    day[2] = 0;

    // strcpy(month, __MONTH__(d));
    char *tmp = __MONTH__(d);
    for (uint16_t i = 0; i < sizeof(__MONTH__(d)); i++)
    {
        month[i] = *tmp;
        tmp++;
    }

    year[0] = d[9];
    year[1] = d[10];
    year[2] = 0;

    // "10" => 0x10
    sscanf_custom(hour, "%x", &HourNum);
    sscanf_custom(day, "%x", &DayNum);
    sscanf_custom(month, "%x", &MonthNum);
    sscanf_custom(year, "%x", &YearNum);

    VAL(VRS_COMPILE_TIME) = (HourNum << 8 | DayNum);
    VAL(VRS_COMPILE_TIME) <<= 16;
    VAL(VRS_COMPILE_TIME) |= (MonthNum << 8 | YearNum);
}

int sscanf_custom(const char *str, const char *format, ...)
{
    va_list args;
    int count;

    va_start(args, format);
    count = vsscanf_custom(str, format, args);
    va_end(args);

    return count;
}

int vsscanf_custom(const char *str, const char *format, va_list args)
{
    int count = 0;

    while (*str && *format)
    {
        if (*format == '%')
        {
            format++;

            if (*format == 'x')
            {
                unsigned int *value = va_arg(args, unsigned int *);
                int result = 0;

                // Skip leading whitespace
                while (*str == ' ' || *str == '\t')
                    str++;

                // Read hexadecimal value
                while ((*str >= '0' && *str <= '9') ||
                       (*str >= 'a' && *str <= 'f') ||
                       (*str >= 'A' && *str <= 'F'))
                {
                    result <<= 4;

                    if (*str >= '0' && *str <= '9')
                        result |= (*str - '0');
                    else if (*str >= 'a' && *str <= 'f')
                        result |= (*str - 'a' + 10);
                    else if (*str >= 'A' && *str <= 'F')
                        result |= (*str - 'A' + 10);

                    str++;
                }

                *value = result;
                count++;
            }
            else
            {
                // Unsupported format specifier
                break;
            }
        }
        else if (*str == *format)
        {
            // Matched literal character
            str++;
            format++;
        }
        else
        {
            // Mismatched character
            break;
        }
    }

    return count;
}
