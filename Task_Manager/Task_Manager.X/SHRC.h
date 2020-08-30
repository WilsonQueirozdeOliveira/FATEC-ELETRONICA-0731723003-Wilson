/******************************************************************************
 * Nome do Arquivo:SHRC.h
 * 
 * Processador:	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	C18 
 *
 * Autor:		Weslley M. Torres
 *
 * Data:		v1 - 09/MAIO/2017 - 
 *
  * Descrição:            Biblioteca adaptada da biblioteca padrão sw_uart.h responsável 
 *                               pelo funcionamento da comunicação serial UART.
 *****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SHRC_H
#define SHRC_H

#include "Config.h"

/* Pino 8 do microcontrolador PIC18F4550 - RE0 */
#define SHIFT_CLOCK         LATBbits.LATB6
/* Pino 9 do microcontrolador PIC18F4550 - RE1 */
#define SHIFT_DATA          LATBbits.LATB5
/* Pino 10 do microcontrolador PIC18F4550 - RE2 */
#define SHIFT_LATCH         LATBbits.LATB7

void SHRC_Controle (uint8_t Data);

void SHRC_Init(void);

#endif	/* SHRC_H */

