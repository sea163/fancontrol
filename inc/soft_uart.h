
#ifndef __SOFT_UART_H
#define __SOFT_UART_H

#include "config.h"

#ifdef DEBUG
    #include <STDIO.H>
    void TxSend(u8 dat);
    void PrintString(const unsigned char *puts);
    // void LOG(const char *str, ...);
    #define LOG printf_tiny
    // #define LOG printf_fast
    // #define LOG printf
#else
    #define LOG(...)
#endif

#endif
