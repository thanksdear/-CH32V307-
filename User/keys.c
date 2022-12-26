#include "keys.h"
/*
 * @fn      Matrix_ssKey_Pin_Init
 * @brief   ���󰴼��ĳ�ʼ��
 * @param
 * @return
 * @note
 *
 */
void Matrix_ssKey_Pin_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
}

/*
 * @fn      Matrix_Key_Scan
 * @brief   ���󰴼�ɨ�裬һ��һ��ɨ��ɨ�����µļ��������ؼ����ֵ
 * @param
 * @return  -1��1��16��ֵ
 * @note
 *
 */
int Matrix_Key_Scan(void)
{
    u8 temp = 0;
    int key_val = -1;

    GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);            //��������
    delay_us(10);

    temp=(GPIO_ReadInputData(GPIOE) >> 8)&0xff;

    //û�а�������ʱɨ��
    if (temp == 0xf0)
    {
            delay_ms(50);
            GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);            //��������
            delay_us(10);
            temp=(GPIO_ReadInputData(GPIOE) >> 8)&0xff;

            if (temp != 0xf0) //��������ʱ���Լ�ֵ���и�ֵ
            {
                //��һ��
                GPIO_Write(GPIOE,0);
                delay_ms(5);
                GPIO_Write(GPIOE,(uint16_t)(0xFE << 8));

                if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                {
                        delay_ms(20);//����

                        if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                        {
                                temp=((GPIO_ReadInputData(GPIOE) >> 8) & 0XFE);     //���н���ɨ��
                                switch(temp)
                                {
                                        case 0xEE:  key_val = 1;   break;
                                        case 0xDE:  key_val = 2;   break;
                                        case 0xBE:  key_val = 3;   break;
                                        case 0x7E:  key_val = 4;   break;
                                        default:    key_val = -1;   break;
                                }
                        }
                }

                //�ڶ���
                GPIO_Write(GPIOE,0);
                delay_ms(5);
                GPIO_Write(GPIOE,(uint16_t)(0xFD << 8));

                if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0)!= 0XF0)
                {
                        delay_ms(20);

                        if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                        {
                                temp=((GPIO_ReadInputData(GPIOE) >> 8) & 0XFD);
                                switch(temp)
                                {
                                        case 0xED:  key_val = 5;   break;
                                        case 0xDD:  key_val = 6;   break;
                                        case 0xBD:  key_val = 7;   break;
                                        case 0x7D:  key_val = 8;   break;
                                        default:    key_val = -1;   break;
                                }
                        }
                }

                //������
                GPIO_Write(GPIOE,0);
                delay_ms(5);
                GPIO_Write(GPIOE,(uint16_t)(0xFB << 8));

                if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                {
                        delay_ms(20);

                        if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                        {
                                temp=((GPIO_ReadInputData(GPIOE) >> 8) & 0XFB);
                                switch(temp)
                                {
                                        case 0xEB:  key_val = 9;   break;
                                        case 0xDB:  key_val = 10;   break;
                                        case 0xBB:  key_val = 11;   break;
                                        case 0x7B:  key_val = 12;   break;
                                        default:    key_val = -1;   break;
                                }
                        }
                }

                //������
                GPIO_Write(GPIOE,0);
                delay_ms(5);
                GPIO_Write(GPIOE,(uint16_t)(0xF7 << 8));

                if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) !=0XF0)
                {
                        delay_ms(20);

                        if(((GPIO_ReadInputData(GPIOE) >> 8) & 0XF0) != 0XF0)
                        {
                                temp=((GPIO_ReadInputData(GPIOE) >> 8) & 0XF7);
                                switch(temp)
                                {
                                        case 0xE7:  key_val = 13;   break;
                                        case 0xD7:  key_val = 14;   break;
                                        case 0xB7:  key_val = 15;   break;
                                        case 0x77:  key_val = 16;   break;
                                        default:    key_val = -1;   break;
                                }
                        }
                    }
                }
            }

    return key_val;

}
