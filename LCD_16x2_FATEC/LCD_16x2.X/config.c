/* 
 * Nome do Arquivo    : config.c
 * 
 * Descricao                 : Armazena funcoes dedicados ao processador.
 * 
 * Ambiente                  : MPLAB X v3.65 Compiler XC8 V1.45(Free Mode); Processador: PIC18f4550.
 * 
 * Responsavel              : Wilson Queiroz de Oliveira.
 * 
 * Vesao/Data               : 1.0V  29/08/2020
 */

#include "config.h"

void config_mcc(void) 
{
    /*
     * config IO
     */
    
    /*
     * LCD output
     */
    LCD_trisd = 0X00;
    
    /*
     * OFF ADC
     */
    ADCON1 = 0x0F;
  
}

