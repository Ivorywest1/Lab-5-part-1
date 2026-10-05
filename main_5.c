/*
 * File:   main.c
 * Author: Julian Barbosa
 *
 * Lab 5 Part 1 - LCD Interface + Counter (0-15) + Round
 * ECE 3301L - Introduction to Microcontrollers Laboratory
 *
 * Description:
 *   Displays a counter (0-15) and a Round variable on a character LCD.
 *   The counter increments every second and resets to 0 after 15.
 *   Round increments each time the counter resets to 0.
 *
 * LCD Pin Assignments (from Figure 1):
 *   RD0 = RS
 *   RD2 = EN
 *   RA4 = D4
 *   RA5 = D5
 *   RA6 = D6
 *   RA7 = D7
 *
 * The LCD driver (LCD.c / LCD.h) is PROVIDED - do not modify LCD.c.
 * Check that the pin #defines at the top of LCD.h match the wiring above.
 * Useful functions:
 *   LCD_init(), LCD_cursor_set(row, col),
 *   LCD_write_string("..."), LCD_write_variable(value, width)
 */

#include <xc.h>
#include <stdint.h>
#include "PIC18F46K22-Config.h"
#include "LCD.h"
#include "LCD.c"

#define _XTAL_FREQ 16000000UL   // 16 MHz HFINTOSC

static void init(void)
{
    // Select 16 MHz HFINTOSC
    OSCCONbits.IRCF = 0b1111;
    OSCCONbits.SCS  = 0b10;

    // Disable analog functionality
    ANSELA = 0x00;
    ANSELD = 0x00;

    // Configure LCD pins as outputs
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD2 = 0;
}

void main(void){
    init();
    LCD_init();

    int16_t counter = 0;
    int16_t round = 0;

    LCD_cursor_set(1, 1);
    LCD_write_string("Counter:");

    LCD_cursor_set(2, 1);
    LCD_write_string("Round:");

    while (1){
        LCD_cursor_set(1, 9);
        LCD_write_variable(counter, 2);

        LCD_cursor_set(2, 7);
        LCD_write_variable(round, 2);

        __delay_ms(1000);

        counter++;

        if (counter > 15){
            counter = 0;
            round++;
        }
    }
}