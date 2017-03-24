/*
 * File:   MCP4726.c
 * Author: evaota
 *
 * Created on 2017/03/02, 18:30
 */

#include "MCP4726.h"

static Voltage_Reg VoltageReg;
static Memory_Reg MemoryReg;


int8_t DAC_WriteVoltage(uint16_t volue)
{
    int8_t result;
    
    VoltageReg.Command = VOLTAGE_COMMAND;
    VoltageReg.PowerDown = 0x00;
    VoltageReg.Voltage4bits = (uint8_t)(volue&0x0F00)>>8;
    VoltageReg.Voltage8bits = (uint8_t)(volue&0x00FF);
    
    result = I2C_Transmit(I2C2_MODULE,DAC_ADDRESS,VoltageReg.Voltage_Data,2);
    return result;
}

