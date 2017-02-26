/*
 * File:   eeprom.c
 * Author: evaota
 *
 * Created on 2017/02/26, 14:14
 */
#include "eeprom.h"

int8_t EEPROM_MultiWrite(uint8_t *pData,uint8_t size,uint8_t addr)
{
    uint8_t i = 0;

    for(;i<size;i++)
    {
        if((addr+i)>EEPROM_SIZE)
            return EXIT_FAILURE;
        eeprom_write(addr+i,pData[i]);
    }

    return EXIT_SUCCESS;
}

int8_t EEPROM_MultiRead(uint8_t *pData,uint8_t size,uint8_t addr)
{
    uint8_t i = 0;

    for(;i<size;i++)
    {
        if((addr+i)>EEPROM_SIZE)
            return EXIT_FAILURE;
        pData[i] = eeprom_read(addr+i);
    }

    return EXIT_SUCCESS;
}