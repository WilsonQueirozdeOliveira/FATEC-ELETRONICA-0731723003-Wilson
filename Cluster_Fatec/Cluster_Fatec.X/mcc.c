/*IDE: MPLAB X v3.65 Compiler XC8(Free Mode) V1.45
 * File:   mcc.c
 * Author: wilson
 *
 * Created on 21 de Abril de 2020, 22:48
 */

#include "Config.h"

void CONFIG_mcc(void) 
{

    /*config IO*/
    TRIS_LED = 0;
    LEDs = 0xff;
    /*config IO*/
    
    CMCON = 0x07; // comparetors off

    /*config timer0*/                 

    /*config timer0*/
    
   /*config_interrupt*/
    RCONbits.IPEN = 1; 
    INTCONbits.GIE = 1;    
    INTCONbits.GIE_GIEH = 1;
    INTCONbits.PEIE_GIEL = 1;
   /*config_interrupt*/
}