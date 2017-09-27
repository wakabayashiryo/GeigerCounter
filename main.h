/* 
 * File:   main.h
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "Timer1_Count.h"
#include "LCD1602.h"
#include "PIC_I2C.h"
#include "MCP4726.h"
#include "eeprom.h"
#include "PIC_mTouch.h"
#include "PIC_Timer6.h"
#include "Buzzer.h"


#define SERIAL_NO   0x01
#define SOFTWARE_VER "1.01"

// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Disable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
    
#define _XTAL_FREQ 32000000

typedef enum
{
    STOPPING = 0x00,
    COUNTING = 0x01,
    RESULT = 0x02,
    SETTING = 0x03,
    SHOW_CONFIG = 0x04,
}STATE_OF_MODE;


#define NUM_OF_DATA 3 
typedef struct
{
    union
    {
        uint8_t Eeprom_table[NUM_OF_DATA]; 
        struct
        {
            uint8_t SerialNum;
            uint8_t GainElements;
            uint8_t DeviceNum;
        };
    };
}PMT_CONFIGURATION;

#define LED_ON      0
#define LED_OFF     1
#define LED_TOG     !LATA6
#define LED_BLUE(x) LATA6 = x 

#define START_SYMBOL 0x00        
#define RESET_SYMBOL 0x01
#define STOP_SYMBOL  0x02
    
#define START_SYMBOL_PARAM 100        
#define RESET_SYMBOL_PARAM 100
#define STOP_SYMBOL_PARAM  100

void I2C2_Init_Port(void);
#include "User_Interface.h"

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

