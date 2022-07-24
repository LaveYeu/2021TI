/*
 * trx.h
 *
 *  Created on: 2021Äê3ÔÂ30ÈÕ
 *      Author: zhouw
 */

#ifndef CODE_TRX_H_
#define CODE_TRX_H_

#include "headfile.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

void User_Tx(int16_t data1, int16_t data2);
uint8_t User_Rx(int16_t *data1, int16_t *data2);


#endif /* CODE_TRX_H_ */
