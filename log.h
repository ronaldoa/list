#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include "types.h"

#define DBG 1
#define DBG_IN 0x0001
#define DBG_OUT 0x0002
#define DBG_INFO 0x0004
#define DBG_WARN 0x0008
#define DBG_ERROR 0x0010
#define DBG_ALL 0xFFFF


extern UINT_T dbg_flags;

#if DBG
    #define MY_PRINTF(flag, format,...)\
        do {\
            if(dbg_flags | flag)\
            printf("FILE:%s,LINE:%d "format, __FILE__,__LINE__,##__VA_ARGS__);\
        }while(0)
#else
    #define MY_PRINTF(fmt,...)
#endif

#endif

