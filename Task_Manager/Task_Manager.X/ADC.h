/******************************************************************************
 * Nome do Arquivo:	 ADC.h
 * 
 * Processador:	 PIC18F4550
 * Op��o de Clock:	 HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	 C18 
 *
 * Autor:		 Weslley M. Torres
 *
 * Data:		 v1 - 09/MAIO/2017 - 
 *
 * Descri��o:              Biblioteca adaptada da biblioteca padr�o sw_uart.h respons�vel 
 *                                pelo funcionamento da comunica��o serial UART.
 *****************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "Config.h"	

uint16_t adc_read (uint8_t canal);

#endif


