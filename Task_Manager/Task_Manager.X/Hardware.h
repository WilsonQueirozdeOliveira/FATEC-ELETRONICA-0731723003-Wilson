/******************************************************************************
 * Nome do Arquivo:	Hardware.c
 * 
 * Processador:	PIC18F4550
 * Opção de Clock:   HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	XC8 
 *
 * Autor:		Weslley M. Torres
 *
 * Data:		v1 - 05/May/2019 - Initial revision 
 *
 * Descrição:       Realiza a configuração dos perifericos internos
 * do microcontrolador PIC18F4550
 * 
 *	Notas:
 *	
 *****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef HARDWARE_H
#define HARDWARE_H

#define _XTAL_FREQ 48000000

void Init_Ports(void);

void ConfigTimer0(void);

void InitHardware(void);

#define SDA_EEPROM_PORT                                                         PORTAbits.RA2
#define SDA_EEPROM_PORT_MODE                                           TRISAbits.RA2
#define _SET_SDA_EEPROM_PORT                                              SDA_EEPROM_PORT = 1
#define _CLEAR_SDA_EEPROM_PORT                                        SDA_EEPROM_PORT = 0
#define _CONFIGURE_SDA_EEPROM_OUTPUT_PORT             SDA_EEPROM_PORT_MODE = 0
#define _CONFIGURE_SDA_EEPROM_INPUT_PORT                 SDA_EEPROM_PORT_MODE = 1

#define SCL_EEPROM_PORT                                                          PORTAbits.RA3
#define SCL_EEPROM_PORT_MODE                                            TRISAbits.RA3
#define _SET_SCL_EEPROM_PORT                                               SCL_EEPROM_PORT = 1
#define _CLEAR_SCL_EEPROM_PORT                                         SCL_EEPROM_PORT = 0
#define _CONFIGURE_SCL_EEPROM_OUTPUT_PORT               SCL_EEPROM_PORT_MODE = 0
#define _CONFIGURE_SCL_EEPROM_INPUT_PORT                   SCL_EEPROM_PORT_MODE = 1

#define LED_BUZZER                                  PORTAbits.RA4
#define LED_BUZZER_PORT_MODE        TRISAbits.RA4 = 0

//BOTOES
#define CHAVE_B1                                        PORTEbits.RE0
#define CHAVE_B1_PORT_MODE              TRISEbits.RE0 = 1

#define CHAVE_B2                                        PORTEbits.RE1
#define CHAVE_B2_PORT_MODE              TRISEbits.RE1 = 1

/*proteus
 * (PIN 14) dado(pic38)RB5
 * (PIN 11) clock(pic39)RB6
 * (PIN 12) enable(pic40)RB7
 */

#define ENABLE_RD           PORTBbits.RB7
#define CLOCK                     PORTBbits.RB6
#define DADO                       PORTBbits.RB5

#define ENABLE_TRIS         TRISBbits.TRISB7 = 0;
#define CLOCK_TRIS           TRISBbits.TRISB6 = 0;
#define DADO_TRIS             TRISBbits.TRISB5 = 0;

#endif	/* HARDWARE_H */

