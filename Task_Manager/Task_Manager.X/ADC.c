/******************************************************************************
 * Nome do Arquivo:	 ADC.c
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

#include "Config.h" 
#include "ADC.h"

/**
 *  \brief Brief
 *  
 *  \param [in] canal Selecao do canal do conversor AD
 *  \return Leitura: valor lido pelo conversor AD
 *  
 *  \details Realiza a leitura do conversor AD e retorna a leitura
 */
uint16_t adc_read(uint8_t canal)
{
    uint16_t Leitura;
    ADCON0bits.CHS = canal;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;              // Inicia Convers�o A/D
    __delay_ms(10);
    if(ADCON0bits.GO_DONE == 0)
    {
        Leitura = (ADRESH<<8)+ADRESL; // Monta uma word  
    }
    ADCON0bits.ADON = 0;
    return(Leitura);
}

