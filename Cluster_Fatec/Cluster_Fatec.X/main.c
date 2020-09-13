/*IDE: MPLAB X v3.65 Compiler XC8(Free Mode) V1.45
 * File:   main.c
 * Author: wilson
 *
 *
 */

#include "Config.h"

__interrupt (high_priority) void high_ISR(void)
{
    screen_1();
    LEDs++;
     if ( 1 == UART_Data_Ready())
        {            
            uart_test_char = UART_Read();
        }
    if ( 1 == UART_TX_Empty())
        {
            UART_Write(uart_test_char);
            //UART_Write_String("\r\n");
            UART_Write_String("wilson"); 
        }
}

void main(void) 
{
    CONFIG_mcc();
    CONFIG_lcd16x2();
    Init_UART();
    while(1) 
    {
        
    }
    return;
}