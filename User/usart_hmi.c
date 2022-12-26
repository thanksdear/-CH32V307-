#include "usart_hmi.h"
#include "debug.h"
void delay(vu32 count)
{
    for(;count!=0;count--);
}
/*
 * @fn      HMISendInit
 * @brief   �������ĳ�ʼ��
 * @param
 * @return
 * @note
 *
 */
void HMISendInit(void)
{
    delay(0xfff);
    USART_SendData(USART1,0x00);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
    USART_SendData(USART1,0xff);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
    USART_SendData(USART1,0xff);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
    USART_SendData(USART1,0xff);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};
    delay(0xfff);
}

void HMISends(char *buf1)
{
    u8 i=0;
    while(1)
    {
        if(buf1[i] != 0)
        {
            USART_SendData(USART1,buf1[i]);  //����һ���ֽ�
            while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
            i++;
        }
        else
        {
            return ;
        }
    }
}

void HMISendb(u8 k)
 {
     u8 i;
     for(i=0; i<3; i++)
     {
             if(k != 0)
             {
                 USART_SendData(USART1,k);  //����һ���ֽ�
                 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
             }
             else
             {
                 return ;
             }
     }
 }
