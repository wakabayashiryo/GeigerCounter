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
#include "main.h"
    
#define TMR1_START() TMR1ON = 1;
#define TMR1_STOP() TMR1ON = 0;



#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

