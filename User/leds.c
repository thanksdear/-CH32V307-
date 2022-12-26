#include "leds.h"
/*
 * @fn      LED_INIT
 * @brief   使输入的值的对应LED灯点亮
 * @param   数值0-12
 * @return
 * @note    这里采用查理复用，可以控制的led个数为n个灯，两两组合的有序排列组合值，也就是N*(N-1)
  *                     对于需要点亮的LED灯，在正方向的IO口输出高电平，反方向的IO口输出低电平，其余设置成浮空
  *                    输入（高阻态），这个样子可以最大利用IO口点亮更多的LED灯。
 *
 */
void LED_INIT(unsigned int num)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    switch(num)
    {
    case 0:
        GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
        break;
    case 1:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_1);
        GPIO_ResetBits(GPIOD, GPIO_Pin_2);
        break;
    case 2:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_2);
        GPIO_ResetBits(GPIOD, GPIO_Pin_1);
        break;
    case 3:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_1);
        GPIO_ResetBits(GPIOD, GPIO_Pin_3);
        break;
    case 4:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_3);
        GPIO_ResetBits(GPIOD, GPIO_Pin_1);
        break;
    case 5:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_1);
        GPIO_ResetBits(GPIOD, GPIO_Pin_4);
        break;
    case 6:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_4);
        GPIO_ResetBits(GPIOD, GPIO_Pin_1);
        break;
    case 7:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_2);
        GPIO_ResetBits(GPIOD, GPIO_Pin_3);
        break;
    case 8:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_3);
        GPIO_ResetBits(GPIOD, GPIO_Pin_2);
        break;
    case 9:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_2);
        GPIO_ResetBits(GPIOD, GPIO_Pin_4);
        break;
    case 10:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_4);
        GPIO_ResetBits(GPIOD, GPIO_Pin_2);
        break;
    case 11:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_3);
        GPIO_ResetBits(GPIOD, GPIO_Pin_4);
        break;
    case 12:
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_4);
        GPIO_ResetBits(GPIOD, GPIO_Pin_3);
        break;
    }
}
