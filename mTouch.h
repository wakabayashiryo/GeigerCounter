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
    
#define CPS_CHANNEL(x) CPSCON1 = (uint8_t)x
#define CPS_ENABLE()   CPSCON0 |= (0x01<<7);       //CPS module is enabled
#define CPS_DISABLE()  CPSCON0 &= ~(0x01<<7);      //CPS module is disabled

void mTouch_Init(void);
void mTouch_Read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MTOUCH_H */

