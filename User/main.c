/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : л����
* Version            : V1.0.0
* Date               : 2022/12/25
* Description        : ���ǵ�һ����ʽд�����ĳ����߼��Ƚϻ��ң��﷨�Ƚϵͼ�������д�겢��֤�ɹ�����ʱ��ʵ�ֹ����˻��ǱȽϻ�ϲ�ġ�
*                                             ���ݼ�飺
*                                             ���ڱ���Ƭ������������������ܹ��������һλ32λ�����֡�
*                                             ͨ���������Ͱ������н��������ô������������ز�ͬ��ֵ����Ƭ�����պ���벻ͬ�Ĵ���ģʽ���ò�ͬ�ķ����������ݣ���󽫽��
*                                             ��ʾ�ڴ������ϣ����ð�����Ϊ�����豸���ڿ�ʼ�����Ȱ��°����ĻὫ�����ֵ��ʾ�ڴ������ϣ����ఴ��������ʾ�򸲸ǡ�
*                                             Ŀǰ��������ģʽ��ģʽһ���������������ֵ����Сֵ�����������һ�����ֵ��ģʽ������������������ʮ�����ڵĸ�������
*                                             ��������������ּ�����ֵ��ģʽ�����ڵ����ʼ�󣬿��԰���������ʾ������š�
*                                             ����ģ�����ģʽ�У�����ʾ�����ֵ������ֵ12ʱ����Ӧֵ��LED�ƻ������
*
*                                             �����飺
*                                             ������ҪΪ�����׶Σ��׶�һ�������жϽ��գ������յ��������������Ƚ����жϽ��ս��գ��Ȱ����ݴ洢����������ģʽһ������
*                                             �׶ζ���rev׼���׶Σ�������ģʽһ������׼���׶Σ���ʼ�����ֲ����������ݽ������ݾ����Ƿ��������׶Σ��׶�������������ʾ����
*                                             ���ģʽ�ڵ�����ģʽһ���������������˸���𽥼�����˸ʱ�䣬����ȷ���������ģʽ�����ڿ�ʼ����԰�������ȷ��������š�

*******************************************************************************/

/*
 *@Note

*/
#include "stdio.h"
#include "debug.h"
#include "oled.h"
#include "rng.h"
#include "leds.h"
#include "keys.h"
#include "usart_hmi.h"
/* Global define */
u8 j = 0;
u8 k = 0;
u8 n = 0;
u8 rev  = 0;
u8 flag = 0;
u32 min = 0;
u32 max = 0;
u8 count = 0;
u8 count2= 0;
u8 ucTemp[42]={0};
u32 a[10]={0};
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void)//�����жϽ���
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE ) != RESET)
    {
        ucTemp[count] = USART_ReceiveData(USART1);

        if (ucTemp[0]=='1'||ucTemp[0]=='2'||ucTemp[0]=='3')count++;//�������ģʽһ�������������ݿ�ʼ�洢��

        if (count==9&&ucTemp[0]=='1')//���������ص�һ��ֵ��4��8λ��ɣ�ģʽһֻ��Ҫ�������ֵ����Сֵ�����Խ��հ˸����ݺ󼴿ɻص���ʼ�׶�
        {                            //���������ص�4��8λ����ֱ���γ�һ����ȷ32λֵ����Ҫ��4��8λֵ�����˹�����׼���׶�rev��
            count=1;                 //���´����ݣ����ڵ�һֵ��Ϊ������ģʽ�����Դӵڶ���ֵ��ʼ
            rev=1;                   //׼���׶α�־λ������ģʽһ��׼���׶�
            flag=0;
        }
        if (ucTemp[count-1]=='a'&&ucTemp[0]=='2')//ģʽ����Ҫ����ʮ��Ŀǰ�������������ֵ����ȷ������������������ý��յ��ַ�a��ص���ʼ�׶�
        {
            count=1;
            rev=2;
            flag=0;
        }
        if (ucTemp[count-1]=='b'&&ucTemp[0]=='3')//ģʽ����Ҫ�ǽ��հ���ֵ���Դ��������ص�ֵû��̫��Ҫ�����ó���ģʽ�����ƵĽ��ո�ʽ
        {
            count=1;
            rev=3;
            flag=0;
        }
    }
}

void GPIO_Toggle_INIT(void)//GPIO�ĵ�ƽ��ת�������Ƶ���˸��ͨ���Ƶ���˸ֱ�۷�ӳ������Ĳ���������ʱ�����仯
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void FMQ_INIT(void)//����������
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE, GPIO_Pin_0);
    GPIO_SetBits(GPIOE, GPIO_Pin_1);
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 i = 0;
    u8 number = 0;
    u16 random = 0;
    u8 key_value = 0;
    u32 max2=0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_Toggle_INIT();
    FMQ_INIT();
    RNG_Init();
    HMISendInit();
    Matrix_ssKey_Pin_Init();//���ֳ�ʼ�������ڣ������������������������������ʱ��
    Delay_Us(500);
    while(1)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));//����˸
        char tjcstr[100]={0};
        if (rev==1)                                                        //ģʽһ׼��
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);
            min=(ucTemp[5])+(ucTemp[6]<<8)+(ucTemp[7]<<16)+(ucTemp[8]<<24);//����4��8λ���ݣ���ԭ32λֵ
            rev=0;                                                         //�ָ�׼���׶α�־λ
            j=0;
            if(max==min&&max==0)
            {
                flag=0;
                count=0;
            }
            else flag=1;                                                   //�����������ֵ������������봮������ʾ�׶Σ��˳�ģʽ
            Delay_Ms(500);                                                 //û����������ͽ��봮������ʾ�׶�
        }
        else if (rev==2)                                                   //ģʽ��׼��
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);//û�����ֵ����Сֵ����������ʡ����max��min������Ϊ�����˳��Ĳ���
            min=(ucTemp[5])+(ucTemp[6]<<8)+(ucTemp[7]<<16)+(ucTemp[8]<<24);
            rev=0;
            j=0;
            if(max==min&&max==0)
            {
                flag=0;
                count=0;
                count2=0;
            }
            else
            {
                for (k=0;k<10;k++)
                {
                    if(ucTemp[4*k+1]==0&&ucTemp[4*k+2]==0&&ucTemp[4*k+3]==0&&ucTemp[4*k+4]==0)break;
                    a[count2]=(ucTemp[4*k+1])+(ucTemp[4*k+2]<<8)+(ucTemp[4*k+3]<<16)+(ucTemp[4*k+4]<<24);
                    if(a[count2]>max2)  max2=a[count2];
                    count2++;
                    flag=2;
                }                                                       //ȷ��������Ч���ָ������������µ����飬����ʵ��
            }

        }
        else if (rev==3)                                                //����ģʽ��׼��
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);//ͬģʽ����û�����ֵ����Сֵ�������˳���
            min=(ucTemp[5])+(ucTemp[6]<<8)+(ucTemp[7]<<16)+(ucTemp[8]<<24);
            rev=0;
            if (max==min&&max==0)
            {
                flag=0;
                count=0;
            }
            else if (max==min&&max==1) flag=3;                           //�����������ģʽ���Ĵ�������ʾ�������˳�������˳���

        }
        if (flag==1)                                                    //ģʽһ���
        {
            RNG_Ready();
            if (j<40)                                                   //������˸40��ֵ
            {
                random=RNG_Get_RandomRange(min,max);
                Delay_Ms(50);
                j++;

            }
            else if (j>39&&j<60)                                        //������˸20��ֵ����˸������
            {
                random=RNG_Get_RandomRange(min,max);
                Delay_Ms(50*(j-39));
                j++;
            }
            else                                                        //����ֵ���֣�ģʽ�����������0��
            {
                flag=0;
                min=0;
                max=0;
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);
                delay_ms(500);
                GPIO_SetBits(GPIOE, GPIO_Pin_1);
            }
            sprintf(tjcstr, "p0.t2.txt=\"%d\"",random);
            HMISends(tjcstr);
            HMISendb(0xff);                                             //��������ʾֵ
            if(max<13)   LED_INIT(random);                              //����أ��������ֵ������13ʱ��led��ֻ��12������Ӧ���led�ƻ����
            else LED_INIT(0);                                           //���򶼲�����
        }
        else if (flag==2)                                               //ģʽ�����
        {                                                               //ģʽ���������ݷ�ʽ����һЩ����
            RNG_Ready();
            if(j<40)
            {
                number=RNG_Get_RandomRange(0,count2-1);
                random=a[number];
                Delay_Ms(50);
                j++;

            }
            else if (j>39&&j<60)
            {
                number=RNG_Get_RandomRange(0,count2-1);
                random=a[number];
                Delay_Ms(50*(j-39));
                j++;
            }
            else
            {
                flag=0;
                count2=0;
                max2=0;
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);
                delay_ms(500);
                GPIO_SetBits(GPIOE, GPIO_Pin_1);
            }
            sprintf(tjcstr, "mode2.t10.txt=\"%d\"",random);
            HMISends(tjcstr);
            HMISendb(0xff);
            if(max2<13)   LED_INIT(random);
            else LED_INIT(0);
        }
        else if (flag==3)                                               //ģʽ�����
        {                                                               //���������13�����������ֵ��ʾ�ڴ������Ͷ�Ӧ��LED����
            key_value=Matrix_Key_Scan();
            LED_INIT(0);
            if(key_value>0&&key_value<13)
            {
                flag=0;
                ucTemp[1]=0;
                sprintf(tjcstr, "mode3.t0.txt=\"%d\"",key_value);
                HMISends(tjcstr);
                HMISendb(0xff);
                LED_INIT(key_value);
                GPIO_ResetBits(GPIOE, GPIO_Pin_0);
                GPIO_SetBits(GPIOE, GPIO_Pin_2);
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);
                delay_ms(250);
                GPIO_SetBits(GPIOE, GPIO_Pin_1);
            }
        }
    }
}
