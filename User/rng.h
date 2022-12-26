#ifndef __RNG_H
#define __RNG_H
#include "ch32v30x.h"
#include "ch32v30x_rng.h"

void RNG_Init(void);

int RNG_Get_RandomRange(int min,int max);

void RNG_Ready(void);



#endif
