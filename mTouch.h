/* 
 * File:   mTouch.h
 * Author: evaota
 *
 * Created on 2017/04/15, 11:06
 */

#ifndef MTOUCH_H
#define	MTOUCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
#define START_SYMBOL 0x00        
#define RESET_SYMBOL 0x01
#define STOP_SYMBOL  0x02
    
#define START_SYMBOL_PARAM 100        
#define RESET_SYMBOL_PARAM 100
#define STOP_SYMBOL_PARAM  100

#define CPS_CHANNEL(x) CPSCON1 = (uint8_t)x
#define CPS_ENABLE()   CPSCON0 |= (0x01<<7);       //CPS module is enabled
#define CPS_DISABLE()  CPSCON0 &= ~(0x01<<7);      //CPS module is disabled

void mTouch_Init(void);
void mTouch_Read(void);
void mTouch_IntervalDecrement(void);
uint8_t mTouch_Check(uint8_t chan);


#ifdef	__cplusplus
}
#endif

#endif	/* MTOUCH_H */

