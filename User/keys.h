#ifndef __KEYS_H
#define __KEYS_H
#include "ch32v30x.h"
#include "debug.h"
#define  delay_us    Delay_Us
#define  delay_ms    Delay_Ms

void Matrix_ssKey_Pin_Init(void);
int Matrix_Key_Scan(void);
#endif
