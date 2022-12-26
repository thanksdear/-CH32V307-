#include "leds.h"
/*
 * @fn      LED_INIT
 * @brief   ʹ�����ֵ�Ķ�ӦLED�Ƶ���
 * @param   ��ֵ0-12
 * @return
 * @note    ������ò����ã����Կ��Ƶ�led����Ϊn���ƣ�������ϵ������������ֵ��Ҳ����N*(N-1)
  *                     ������Ҫ������LED�ƣ����������IO������ߵ�ƽ���������IO������͵�ƽ���������óɸ���
  *                    ���루����̬����������ӿ����������IO�ڵ��������LED�ơ�
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
