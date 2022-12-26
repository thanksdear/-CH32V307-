#include "rng.h"


void RNG_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);
    RNG_Cmd(ENABLE);

}

int RNG_Get_RandomRange(int min,int max)
{
  return RNG_GetRandomNumber()%(max-min+1)+min;
}

void RNG_Ready(void)
{
    while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==RESET)
    {
    }
}
