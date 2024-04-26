#ifndef __Debug_MSG_h__
#define __Debug_MSG_h__
#include <stdio.h>

/* DEBUG INFO LEVEL */
#if defined(DEBUG_INFO)
#define D_INIT_INFO printf("%s::\tinit end\r\n", __FUNCTION__)
#define D_STATE_INFO printf("printf::\tDisable\r\n")
#else
#define D_INIT_INFO
#define D_STATE_INFO
#endif

/* DEBUG ERRORS LEVEL */
#if defined(DEBUG_ERR)
#define D_ERR_MSG_L0 printf("%s::\tcrit err\tline::\t%lu\r\n", __FUNCTION__, __LINE__)
#define D_ERR_MSG_L1 printf("%s::\tl1 err\tline::\t%lu\r\n", __FUNCTION__, __LINE__)
#define D_TIMEOUT_MSG printf("%s::\ttimeout\tline::\t%lu\r\n", __FUNCTION__, __LINE__)
#else
#define D_ERR_MSG_L0
#define D_ERR_MSG_L1
#define D_TIMEOUT_MSG
#endif

#endif //__Debug_MSG_h__