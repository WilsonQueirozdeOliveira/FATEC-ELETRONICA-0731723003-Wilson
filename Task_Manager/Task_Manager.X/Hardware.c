/******************************************************************************
 * Nome do Arquivo:	Hardware.c
 * 
 * Processador:	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
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
#include "Config.h"
#include "Hardware.h"

void Init_ADC( void );

/**
 *  \brief ConfigTimer0
 *  
 *  \return none
 *  
 *  \details Configure timer0 registers
 */
void ConfigTimer0(void)
{
    T0CON   = 0b11000101;
    INTCON  = 0b11100000;
    INTCON2 = 0b10000000;
    INTCON3 = 0b00000000;
    SPPCON  = 0b00000000;
    SPPCFG  = 0b00000000;

    TMR0    = TIMER0_INIT_VALUE;  //Set initial value of TMR0 register (for counting 1ms, as we need)
}
void InitInterrupt(void)
{
    INTCON  = 0b11100000;
    INTCON2 = 0b10000000;
    INTCON3 = 0b00000000;	
    PIE1    = 0b00100000;
}

/**
 *  \brief Init_Ports
 *  
 *  \return none
 *  
 *  \details Initialize ports
 */
void Init_Ports(void)
{
    TRISB = 0x00;            //configure all portb as output
    LATB  = 0xFF;

    /* Inicializa portas conectadas ao CI 74HC595 */
    TRISE = 0x07;
    TRISA = 0x00;
}

/**
 *  \brief Init_ADC
 *  
 *  \return none
 *  
 *  \details Initialize Analog to Digital Converter
 */
void Init_ADC( void )
{	
    ADCON0  = 0b00000001;
//			||||||||--------> ADON
//			|||||||---------> GO/ DONE
//			||||||----------> CHS0
//			|||||-----------> CHS1
//			||||------------> CHS2
//			|||-------------> CHS3
//			||--------------> Não aplicavel
//			|---------------> Não aplicavel

    ADCON1  = 0b00001101;
//			||||||||--------> PCFG0: A/D Port Configuration Control bits
//			|||||||---------> PCFG1: A/D Port Configuration Control bits
//			||||||----------> PCFG2: A/D Port Configuration Control bits
//			|||||-----------> PCFG3: A/D Port Configuration Control bits
//			||||------------> VCFG0: Voltage Reference Configuration bit (VREF+ source), 1 = VREF+ (AN3)/ 0 = VDD
//			|||-------------> VCFG1: Voltage Reference Configuration bit (VREF- source), 1 = VREF- (AN2)/ 0 = VSS
//			||--------------> Não aplicavel
//			|---------------> Não aplicavel
  
     ADCON2 = 0b10000110;
//			||||||||--------> ADCS0: A/D Conversion Clock Select bits
//			|||||||---------> ADCS1: A/D Conversion Clock Select bits
//			||||||----------> ADCS2: A/D Conversion Clock Select bits
//			|||||-----------> ACQT0: A/D Acquisition Time Select bits
//			||||------------> ACQT1: A/D Acquisition Time Select bits
//			|||-------------> ACQT2: A/D Acquisition Time Select bits
//			||--------------> Não aplicavel
//			|---------------> ADFM: A/D Result Format Select bit, 1 = Right justified/ 0 = Left justified
}

void InitHardware(void)
{
    /* Initialize ports */
    Init_Ports();	

    /* Configure Timer0 */
    ConfigTimer0();

    /* Configure ADC */
    Init_ADC();

    /* Configura Interrupcoes*/
    InitInterrupt();
}

