/*
 * File:    (config.h) ECU MONOPONTO - FATEC SANTO ANDRE
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

#ifndef __MCC_H
#define	__MCC_H

#include <xc.h>

#include <stdlib.h>

#include "displayLCD.h"

#define _XTAL_FREQ 48000000

//Define I/Os 

#define Saida_Bico   PORTBbits.RB3    //Liga/desliga BicoInjetor
#define Ocilador    PORTBbits.RB2    //Sinal da Interrupcao de tempo
#define Ent_MAP PORTBbits.RB1    //Interrupcao do sinal do MAP
#define Ent_PIP  PORTBbits.RB0    //Interrupcao do sinal PIP

#define Botao_B1   PORTEbits.RE0
#define Botao_B2   PORTEbits.RE1
#define Botao_B3   PORTEbits.RE3

void delay_ms(int);

#endif

