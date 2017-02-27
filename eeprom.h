/* 
 * File:   eeprom.h
 * Author: evaota
 *
 * Created on 2017/02/26, 14:14
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "main.h"

#ifdef	__cplusplus
extern "C" {
#endif
#define EEPROM_SIZE 256     //Define eeprom size on device

int8_t EEPROM_MultiWrite(uint8_t *pData,uint8_t size,uint8_t addr);
int8_t EEPROM_MultiRead(uint8_t *pData,uint8_t size,uint8_t addr);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

