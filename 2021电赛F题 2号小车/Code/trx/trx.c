/*
 * trx.c
 *
 *  Created on: 2021Äê3ÔÂ30ÈÕ
 *      Author: zhouw
 */


#include "trx.h"


#define     num     2

u8 TX[num*2+4], RX[num*2+4];


void User_Tx(int16_t data1, int16_t data2)
{
    u8 cnt=0;
    u8 i;

    TX[cnt++]=0x5A;
    TX[cnt++]=0x6B;
    TX[cnt++]=data1+data2;

    TX[cnt++]=BYTE1(data1);
    TX[cnt++]=BYTE0(data1);

    TX[cnt++]=BYTE1(data2);
    TX[cnt++]=BYTE0(data2);

    for(i=0; i<cnt; i++)
    printf("%c",TX[i]);
    printf("\n");
}

uint8_t User_Rx(int16_t *data1, int16_t *data2)
{
    u8 i;
    for(i=0; i<num*2+4; i++)
    {
        // RX[i] = USART_ReceiveData(USARTX);
        RX[i] = getchar();
        if(RX[i]=='\n' && i<num*2+3)
        return 0;
    }

    *data1 = RX[3]<<8 | RX[4];
    *data2 = RX[5]<<8 | RX[6];

    if(*data1+*data2 == RX[2])
    return 1;
    else
    return 0;
}
