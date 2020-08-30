/******************************************************************************
 * Nome do Arquivo:	 ADC.h
 * 
 * Processador:	 PIC18F4550
 * Opção de Clock:	 HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	 C18 
 *
 * Autor:		 Weslley M. Torres
 *
 * Data:		 v1 - 09/MAIO/2017 - 
 *
 * Descrição:              Biblioteca adaptada da biblioteca padrão sw_uart.h responsável 
 *                                pelo funcionamento da comunicação serial UART.
 *****************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "Config.h"	

uint16_t adc_read (uint8_t canal);

#endif


