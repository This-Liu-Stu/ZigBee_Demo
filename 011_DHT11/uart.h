#ifndef __UART_H
#define __UART_H

#include "ioCC2530.h"

void InitUart();
void Send_String(char *Data, int len);

#endif 
