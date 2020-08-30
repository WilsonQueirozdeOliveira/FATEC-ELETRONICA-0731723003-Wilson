/******************************************************************************
 * Nome do Arquivo:	 UART.h
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
#ifndef __UART_H
#define __UART_H

/** I N C L U D E S **********************************************************/
#include "Config.h"

/** D E F I N E S ************************************************************/

// Defini��o dos pinos de Transmiss�o(TX) e Recep��o(RX) no PIC18F4550
#define PINO_TX	TRISCbits.RC6
#define PINO_RX	TRISCbits.RC7

/**  P R O T O T I P O  D E  F U N C O E S  **********************************/

/******************************************************************************
 * Funcao:		void UART_Write(char data)
 * Entrada:		(char data) : Caractere que ser� enviado
 * Sa�da:		Nenhuma (void)
 * Descri��o:             (Envia Um caractere no UART).
 *****************************************************************************/
void UART_Write(char data);

/******************************************************************************
 * Funcao:		char UART_TX_Empty();
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:             (Verifica o Registro de Transmiss�o).
 *****************************************************************************/
char UART_TX_Empty();

/******************************************************************************
 * Funcao:		void UART_Write_String(const char *string)
 * Entrada:		*string: Ponteiro que direciona o endere�o dos caracteres de uma string
 * Sa�da:		Nenhuma (void)
 * Descri��o:             Envia uma string na comunica��o UART.
 *****************************************************************************/
void UART_Write_String(const char *string);

/******************************************************************************
 * Funcao:		char UART_Data_Ready();
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:             (Verifica se os dados est�o prontos para a leitura)
 *                               Utiliza o bit de sinaliza��o(Flag) RCIF que ser� definido quando a recep��o
 *                               de dados for conclu�da.
 *****************************************************************************/
char UART_Data_Ready();

/******************************************************************************
 * Funcao:		char UART_Read()
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:             Essa rotina espera at� que a recep��o esteja completa e em seguida
 *                               l� os dados de "8 bits" do registrador RCREG.
 *****************************************************************************/
char UART_Read(void);

/******************************************************************************
 * Funcao:                  void UART_Read_String(char *buffer, unsigned int length)
 * Entrada:                 char *buffer: Ponteiro que direciona para os endere�os dos caracteres
 *                                da string recebida.
 *                                unsigned int length: Tamanho da string que foi recebida.
 * Sa�da:                      Nenhuma (void)
 * Descri��o:               Essa rotina l� uma string a partir do endere�o do primeiro caractere
 *                                 e de seu tamanho.
 *****************************************************************************/
void UART_Read_String(char *buffer, unsigned char length);

/******************************************************************************
 * Funcao:		void UART_Write_INT(int valor)
 * Entrada:		int valor: tipo inteiro sinalizado.
 * Sa�da:                    Nenhuma (void)
 * Descri��o:             Essa rotina envia um valor tipo signed int (de -32768 a 32767)
 *                               pela comunica��o UART, Sendo que este valor � convertido para Unsigned char .
 *****************************************************************************/
void UART_Write_INT(int valor);

/******************************************************************************
 * Funcao:		void Init_UART(void)
 * Entrada:		Nenhuma.
 * Sa�da:                     Nenhuma (void)
 * Descri��o:              Essa fun��o inicializa o periferico UART.
 *****************************************************************************/
void Init_UART(void);

/*********************************FIM****************************************/
#endif