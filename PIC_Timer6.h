/* 
 * File:   PIC_Timer6.h
 * Author: evaota
 *
 * Created on 2017/08/25, 12:14
 */

#ifndef PIC_TIMER6_H
#define	PIC_TIMER6_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
        
typedef enum
{
    TMR6_PRESCALER1 = 0,
    TMR6_PRESCALER4 = 1,
    TMR6_PRESCALER16 = 2,
    TMR6_PRESCALER64 = 3,
}TMR6_PRESCALER_VAL;

void Timer6_Init(TMR6_PRESCALER_VAL pre_val,uint8_t period);
uint8_t Timer6_CheckFlag(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER6_H */

