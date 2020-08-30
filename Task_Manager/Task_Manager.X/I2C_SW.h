/******************************************************************************
 * Nome do Arquivo:	I2C_SW.h
 * 
 * Processador:         PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	C18 
 *
 * Autor:		Weslley M. Torres
 *
 * Data:		v1 - 09/MAIO/2017 - 
 *
 * Descrição:             Biblioteca adaptada da biblioteca padrão sw_uart.h responsável 
 *                               pelo funcionamento da comunicação serial UART.
 *****************************************************************************/

#ifndef  _I2C_SW_H_
#define  _I2C_SW_H_
 
#include "Config.h"
#include "Hardware.h"

unsigned char write_eeprom_byte(unsigned int address, unsigned char byte);
unsigned char read_eeprom_byte(unsigned int address);
void eeprom_init(void);
void Write_FF_On_Eeprom(unsigned char mode);

#ifdef EEPROM_MANIPULATE_WORD
void write_eeprom_word(unsigned int address, unsigned int dado);
unsigned int read_eeprom_word(unsigned int address);
#endif

#ifdef EEPROM_MANIPULATE_BLOCK
unsigned char write_eeprom_block(unsigned int address, unsigned int size, unsigned char *buffer);
unsigned char read_eeprom_block(unsigned int address, unsigned int size, unsigned char *buffer);
#endif

#endif