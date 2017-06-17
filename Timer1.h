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
    
typedef struct
{
    uint32_t Delta_t;
    uint16_t RenewalCPM;
}TimeCounter;
    
typedef struct
{
    uint32_t SigmaDeltaCount;
    uint32_t SigmaCPM;
    uint16_t AverageCPM;
    uint32_t Num_of_Detect;
}Counters;

#define Timer1_Read()   (uint16_t)TMR1
#define Timer1_Write(x)  {TMR1ON = 0;\
                        TMR1 = (uint16_t)x;\
                        TMR1ON = 1;\
                        }   
#define Timer1_Reset()  Timer1_Write(0xFFFF - DELTA_COUNT)
    
void Timer1_Init(void);
void Timer1_StartCount(void);
void Timer1_StopCount(void);
void Timer1_ClearRecord(void);

#define DELTA_COUNT 10UL
uint32_t Timer1_GetCountSum(void);
uint16_t Timer1_GetCPM(void);

void Timer1_Count200us(void);
uint8_t Timer1_DetectAssignCount(void);//put into interrupt function

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

