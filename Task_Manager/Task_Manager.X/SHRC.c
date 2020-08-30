/******************************************************************************
 * Nome do Arquivo:SHRC.c
 * 
 * Processador:	PIC18F4550
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

/**************************************************** I N C L U D E S **************************************************/

#include "Config.h"
#include "SHRC.h"

void ShiftRegister( uint8_t DataToSHRC );
void Escreve_Latch ( void );

/***********************************************************************************************************************/
/**
 * \fn  void SHRC_Init(void)
 * \brief Inicializa as portas do microcontrolador conectadas ao registrador de deslocamento. 
 * 
 * A funcao ira realizar a inicializacao das portas conectadas no CI 74HC595.
 * 
 */

void SHRC_Init(void)
{
    SHIFT_LATCH = t_Low;
    SHIFT_CLOCK = t_Low;
    SHIFT_DATA  = t_Low;
}	
/***********************************************************************************************************************/
/*
 * \fn  void ShiftRegister (unsigned long int LEDs)
 * \brief Capta os valores dos dados e transmite para o CI. 
 * 
 * A funcao ira receber as flags que foram unificadas e representa os valores no leds.
 * 
 * \param[in] i auxilia no envio dos dados.
 * \param[in] Deslocador variavel que contem os dados das flag e que ira auxiliar no envio de valores.
 */

void ShiftRegister(uint8_t DataToSHRC)
{
    uint8_t i=0;
    while(i<=7)
    {
        if((DataToSHRC & 0x80) == 0)
        {
            SHIFT_DATA = 0;
        }
        else
        {
            SHIFT_DATA = 1;
        }
        DataToSHRC = DataToSHRC << 1;
        __delay_us(30);
        SHIFT_CLOCK = 1;
        __delay_us(30);
        SHIFT_DATA  = 0;
        __delay_us(30);
        SHIFT_CLOCK = 0;
        __delay_us(30);
        i++;
    }
}
/***********************************************************************************************************************/

/*****************************************  A T I V A C A O  D O  L A T C H   ******************************************/

/**
 * \fn  void Escreve_Latch (void)
 * \brief Funcao de envio do pulso de Latch do shift register. 
 * 
 * Esta funcao finaliza o processo do shift register.
 *
 */

void Escreve_Latch ( void )
{
    //Inicio da funcao.
    SHIFT_LATCH = 0;
    __delay_us(30);
    SHIFT_LATCH = 1;
    __delay_us(60);
    SHIFT_LATCH = 0;
}
/***********************************************************************************************************************/

void SHRC_Controle  (uint8_t Data)
{    
   ShiftRegister(Data);
   Escreve_Latch();
}