/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : 谢明修
* Version            : V1.0.0
* Date               : 2022/12/25
* Description        : 这是第一份正式写出来的程序，逻辑比较混乱，语法比较低级，但是写完并验证成功、暂时都实现功能了还是比较欢喜的。
*                                             内容简介：
*                                             基于本单片机的随机数发生器，能够随机产生一位32位的数字。
*                                             通过串口屏和按键进行交互。利用串口屏触摸返回不同的值，单片机接收后进入不同的处理模式，用不同的方法处理数据，最后将结果
*                                             显示在串口屏上；利用按键作为抢答设备，在开始后最先按下按键的会将键序号值显示在串口屏上，其余按键不会显示或覆盖。
*                                             目前共有三种模式，模式一：串口屏输入最大值和最小值，输出区域间的一个随机值；模式二：串口屏输入任意十个以内的个数的数
*                                             字输出在输入数字间的随机值；模式三：在点击开始后，可以按键抢答并显示按键序号。
*                                             特殊的，三个模式中，当显示的最大值不超过值12时，对应值的LED灯会点亮。
*
*                                             代码简介：
*                                             整体主要为三个阶段，阶段一（串口中断接收）：接收到串口屏的数据先进行中断接收接收，先把数据存储，并区分于模式一二三；
*                                             阶段二（rev准备阶段）：进入模式一二三的准备阶段，初始化部分参数，并根据接收数据决定是否进入输出阶段；阶段三（串口屏显示），
*                                             输出模式内的数，模式一二的随机数不断闪烁，逐渐减少闪烁时间，最终确定随机数。模式三，在开始后可以按键抢答，确定按键序号。

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
void USART1_IRQHandler(void)//串口中断接收
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE ) != RESET)
    {
        ucTemp[count] = USART_ReceiveData(USART1);

        if (ucTemp[0]=='1'||ucTemp[0]=='2'||ucTemp[0]=='3')count++;//如果进入模式一、二、三，数据开始存储。

        if (count==9&&ucTemp[0]=='1')//串口屏返回的一个值由4个8位组成，模式一只需要处理最大值和最小值，所以接收八个数据后即可回到初始阶段
        {                            //串口屏返回的4个8位不能直接形成一个正确32位值，需要对4个8位值处理，此过程在准备阶段rev中
            count=1;                 //重新存数据，由于第一值是为了区分模式，所以从第二个值开始
            rev=1;                   //准备阶段标志位，进入模式一的准备阶段
            flag=0;
        }
        if (ucTemp[count-1]=='a'&&ucTemp[0]=='2')//模式二需要接收十（目前）内任意个数的值，不确定具体个数，所以设置接收到字符a后回到初始阶段
        {
            count=1;
            rev=2;
            flag=0;
        }
        if (ucTemp[count-1]=='b'&&ucTemp[0]=='3')//模式三主要是接收按键值，对串口屏返回的值没有太多要求，设置成于模式二类似的接收格式
        {
            count=1;
            rev=3;
            flag=0;
        }
    }
}

void GPIO_Toggle_INIT(void)//GPIO的电平翻转，用作灯的闪烁，通过灯的闪烁直观反映随机数的产生及产生时间间隔变化
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void FMQ_INIT(void)//蜂鸣器配置
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
    Matrix_ssKey_Pin_Init();//各种初始化，串口，随机数发生器、串口屏、按键、延时。
    Delay_Us(500);
    while(1)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));//灯闪烁
        char tjcstr[100]={0};
        if (rev==1)                                                        //模式一准备
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);
            min=(ucTemp[5])+(ucTemp[6]<<8)+(ucTemp[7]<<16)+(ucTemp[8]<<24);//处理4个8位数据，还原32位值
            rev=0;                                                         //恢复准备阶段标志位
            j=0;
            if(max==min&&max==0)
            {
                flag=0;
                count=0;
            }
            else flag=1;                                                   //如果传进来的值符合情况不进入串口屏显示阶段，退出模式
            Delay_Ms(500);                                                 //没有其他情况就进入串口屏显示阶段
        }
        else if (rev==2)                                                   //模式二准备
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);//没有最大值和最小值，这里是我省事用max和min继续作为用于退出的参数
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
                }                                                       //确定输入有效数字个数，并存入新的数组，便于实用
            }

        }
        else if (rev==3)                                                //进入模式三准备
        {
            max=(ucTemp[1])+(ucTemp[2]<<8)+(ucTemp[3]<<16)+(ucTemp[4]<<24);//同模式二，没有最大值和最小值，用于退出。
            min=(ucTemp[5])+(ucTemp[6]<<8)+(ucTemp[7]<<16)+(ucTemp[8]<<24);
            rev=0;
            if (max==min&&max==0)
            {
                flag=0;
                count=0;
            }
            else if (max==min&&max==1) flag=3;                           //正常情况进入模式三的串口屏显示，符合退出情况就退出。

        }
        if (flag==1)                                                    //模式一输出
        {
            RNG_Ready();
            if (j<40)                                                   //快速闪烁40个值
            {
                random=RNG_Get_RandomRange(min,max);
                Delay_Ms(50);
                j++;

            }
            else if (j>39&&j<60)                                        //减速闪烁20个值，闪烁逐渐慢下
            {
                random=RNG_Get_RandomRange(min,max);
                Delay_Ms(50*(j-39));
                j++;
            }
            else                                                        //最终值出现，模式清楚，参数归0。
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
            HMISendb(0xff);                                             //串口屏显示值
            if(max<13)   LED_INIT(random);                              //特殊地，设置最大值不超过13时（led灯只画12个）对应序号led灯会点亮
            else LED_INIT(0);                                           //否则都不亮。
        }
        else if (flag==2)                                               //模式二输出
        {                                                               //模式二处理数据方式多了一些步骤
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
        else if (flag==3)                                               //模式三输出
        {                                                               //如果不超过13，按键的序号值显示在串口屏和对应的LED灯上
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
