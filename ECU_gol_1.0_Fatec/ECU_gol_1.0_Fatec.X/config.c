/*
 * File:    (config.c) ECU MONOPONTO - FATEC SANTO ANDRE
 * Processor:   PIC18f4550
 * Conpiler:    MPLAB X v3.65 + XC8 v1.45
 * Company: FATEC Santo Andre
 * Author:  Prof. Edson Kitani
 * Date:  12/02/2019
 *
 * Software License Agreement: Somente para fins didaticos
 * 
 ********************************************************************************
 * File Description: 
 * Este programa funciona como uma ECU de EFI Monoponto para o
 * veiculo GOl.
 * Esta versao e usada no Lab para teste das placas.
 * Change History
 * 1.0 29/08/2019 
 * 2020 update: wilson Queiroz de Oliveira
 */

#include "config.h"

void delay_ms(int delaytime)
{
    while (--delaytime)
    {
        __delay_ms(1);
    }  
}
