/*
 * File:   MCP4726.c
 * Author: evaota
 *
 * Created on 2017/03/02, 18:30
 */

#include "MCP4726.h"

static Config_Reg  ConfigReg;
static Voltage_Reg VoltageReg;
//static Memory_Reg  MemoryReg;

void DAC_Initialize(void)
{
    I2C_Init(I2C2_MODULE,0x00,I2C_MODE_MASTER,I2C_SPEED_STANDARD);

    ConfigReg.Command = CONFIG_COMMAND;
    ConfigReg.Gain = 0x00;
    ConfigReg.PowerDown = 0x00;
    ConfigReg.Voltage_Ref = 0x00;

    I2C_Transmit(I2C2_MODULE,DAC_ADDRESS,ConfigReg.Config_Data,1);

}

int8_t DAC_WriteVoltage(uint16_t volue)
{
    VoltageReg.Command = VOLTAGE_COMMAND;
    VoltageReg.PowerDown = ConfigReg.PowerDown;
    VoltageReg.Voltage4bits = (uint8_t)((volue&0x0F00)>>8);
    VoltageReg.Voltage8bits = (uint8_t)(volue&0x00FF);
    
    return I2C_Transmit(I2C2_MODULE,DAC_ADDRESS,VoltageReg.Voltage_Data,2);
}

