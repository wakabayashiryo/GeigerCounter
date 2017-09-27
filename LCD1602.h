/* 
 * File:   LCD1602.h
 * Author: evaota
 *
 * Created on 2017/02/25, 23:07
 */

#ifndef LCD1602_H
#define	LCD1602_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
#define BUS_PORT        PORTB           //define bus port
                                        //Bus Bit control
#define	LCD1602_BUS(data) 	BUS_PORT = (       \
                        ((data&0x0C)<<1)|(data&0x03)\
                        )      
#define LCD1602_E           LATA4             // Cotrol bit Enable			
#define LCD1602_RS          LATA3             // Cotrol bit Resisiter Select 	
                                        //MCU make LCD reading data or command.
#define LCD1602_STROBO()    {LCD1602_E = 1;        \
                        __delay_us(1);   \
                        LCD1602_E = 0;         \
                        __delay_us(1);}    
    
typedef void (*LCD1602_Init_PORTTypedef)(void);                        

void LCD1602_Init(LCD1602_Init_PORTTypedef LCD1602_Init_PORT);
void LCD1602_Put(int8_t word);
void putch(char c);
void LCD1602_DisplayClear(void);
void LCD1602_CursorHome(void);
void LCD1602_CursorPosition(uint8_t tx ,uint8_t ty);
void LCD1602_CursorShift(uint8_t shift,uint8_t RL);
void LCD1602_DispShift(uint8_t shift,uint8_t RL);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD1602_H */

