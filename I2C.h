/*
 * File:   I2C.h
 * Author: evaota
 *
 * Created on 2017/03/5, 14:24
 */
#ifndef I2C_H
#define	I2C_H

#include "main.h"

/*TODO
 * test i2C2
 * copy i2c1
 * test all function
 */

#define I2C1_NOT_USE 0
#define I2C2_NOT_USE 0

#define SLAVE_RECEIVE_MAX 8

typedef enum
{
    I2C_MODE_MASTER,
    I2C_MODE_SLAVE
}I2Cx_Mode;

typedef enum
{
    I2C_SPEED_STANDARD,
    I2C_SPEED_HIGH,
    I2C_SPEED_NONE
}I2Cx_Speed;

typedef enum
{
    I2C1_MODULE,
    I2C2_MODULE
}I2Cx_Module;

typedef struct 
{
    uint8_t SlaveTransmitBuff[SLAVE_RECEIVE_MAX];
    uint8_t SlaveReceiveBuff[SLAVE_RECEIVE_MAX];
    uint8_t *TransmitPoint;
    uint8_t *ReceivePoint;
    I2Cx_Mode Mode;
}I2Cx_Configuration;

void I2C1_Setting(uint8_t address,I2Cx_Mode mode,I2Cx_Speed Speed);
void I2C1_Interrupt(void);
int8_t I2C1_Transmit(uint8_t address,uint8_t *pData,uint8_t size);
int8_t I2C1_Receive(uint8_t address,uint8_t *pData,uint8_t size);

void I2C2_Setting(uint8_t address,I2Cx_Mode mode,I2Cx_Speed Speed);
void I2C2_Interrupt(void);
int8_t I2C2_Transmit(uint8_t address,uint8_t *pData,uint8_t size);
int8_t I2C2_Receive(uint8_t address,uint8_t *pData,uint8_t size);

void I2C_Init(I2Cx_Module I2Cx,uint8_t address,I2Cx_Mode mode,I2Cx_Speed Speed);
int8_t I2C_Transmit(I2Cx_Module I2Cx,uint8_t address,uint8_t *pData,uint8_t size);
int8_t I2C_Receive(I2Cx_Module I2Cx,uint8_t address,uint8_t *pData,uint8_t size);
void I2C_CommonInterrupt(void);

#endif	/* I2C_H */

