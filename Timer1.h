/* 
 * File:   Timer1.h
 * Author: evaota
 *
 * Created on 2017/02/26, 14:38
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <math.h>
#include "main.h"
#include <string.h>
    
typedef struct
{
    uint8_t Second_t;
    uint8_t Minute_t;
    uint32_t Delta_t;
    uint16_t RenewalRersult;
}TimeCounter;
    
typedef struct
{
    uint32_t SigmaDeltaCount;
}Counters;

#define Timer1_Read()   (uint16_t)TMR1
#define Timer1_Write(x)  {TMR1ON = 0;\
                        TMR1 = (uint16_t)x;\
                        TMR1ON = 1;\
                        }   
#define Timer1_Reset()  Timer1_Write(0xFFFF-DELTA_COUNT+1)
    
void Timer1_Init(void);
void Timer1_StartCount(void);
void Timer1_StopCount(void);
void Timer1_ClearRecord(void);

#define DELTA_COUNT 2UL

uint32_t Timer1_GetCountSum(void);
uint32_t Timer1_GetCPM(void);
uint32_t Timer1_GetCPS(void);
uint8_t Timer1_GetSecond(void);
uint8_t Timer1_GetMinute(void);

void Timer1_Count1ms(void);
uint8_t Timer1_DetectAssignCount(void);//put into interrupt function

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

