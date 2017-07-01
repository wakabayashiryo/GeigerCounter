/* 
 * File:   User_Interface.h
 * Author: evaota
 *
 * Created on 2017/07/02, 1:09
 */

#ifndef USER_INTERFACE_H
#define	USER_INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"

void StartUp_Menu(PMT_CONFIGURATION *data);
void Ssetting_PMT_Config(PMT_CONFIGURATION *data);
void Show_PMT_Config(PMT_CONFIGURATION *data);

#ifdef	__cplusplus
}
#endif

#endif	/* USER_INTERFACE_H */

