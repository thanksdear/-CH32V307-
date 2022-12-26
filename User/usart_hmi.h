#ifndef __USART_HMI_H
#define __USART_HMI_H
#include "ch32v30x.h"
void HMISendInit(void);
void HMISends(char *buf1);
void HMISendb(u8 buf);

#endif
