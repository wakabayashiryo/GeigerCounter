/*
 * File:   eeprom.c
 * Author: evaota
 *
 * Created on 2017/02/26, 14:14
 */
#include "eeprom.h"
/*-----------------------------------------------------------------
 * Feature:
 *  This fuction can write some data to eeprom
 -----------------------------------------------------------------*/
int8_t EEPROM_MultiWrite(uint8_t *pData,uint8_t size,uint8_t addr)
{
    uint8_t i = 0;

    for(;i<size;i++)
    {
        if((addr+i)>EEPROM_SIZE-1)  //if address eceed eeprom size of size.
            return EXIT_FAILURE;    //this function return error
        eeprom_write(addr+i,pData[i]);
    }

    return EXIT_SUCCESS;
}

/*-----------------------------------------------------------------
 * Feature:
 *  This fuction can read some data from eeprom
 -----------------------------------------------------------------*/
int8_t EEPROM_MultiRead(uint8_t *pData,uint8_t size,uint8_t addr)
{
    uint8_t i = 0;

    for(;i<size;i++)
    {
        if((addr+i)>EEPROM_SIZE-1)  //if address eceed eeprom size of size.
            return EXIT_FAILURE;    //this function return error
        pData[i] = eeprom_read(addr+i);
    }

    return EXIT_SUCCESS;
}