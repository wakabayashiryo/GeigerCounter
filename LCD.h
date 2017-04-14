/* 
 * File:   LCD.h
 * Author: evaota
 *
 * Created on 2017/02/25, 23:07
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
    
#define BUS_PORT        PORTB           //define bus port
                                        //Bus Bit control
#define	LCD_BUS(data) 	BUS_PORT = (       \
                        ((data&0x0C)<<1)|(data&0x03)\
                        )      
#define LCD_E           LATA4             // Cotrol bit Enable			
#define LCD_RS          LATA3             // Cotrol bit Resisiter Select 	
                                        //MCU make LCD reading data or command.
#define LCD_STROBO()    {LCD_E = 1;        \
                        __delay_us(1);   \
                        LCD_E = 0;         \
                        __delay_us(1);}    
    
void LCD_Init(void);
void LCD_Put(int8_t word);
void LCD_DisplayClear(void);
void LCD_CursorHome(void);
void LCD_CursorPosition(uint8_t tx ,uint8_t ty);
void LCD_CursorShift(uint8_t shift,uint8_t RL);
void LCD_DispShift(uint8_t shift,uint8_t RL);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD2_H */

