/******************************************************************************
 * Nome do Arquivo:	displayLCD.c
 * Dependencias:	Veja arquivo "UART.h"
 * Processador:		PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:		C18 
 *
 * Autor:			
 *
 * Data:			v1 - 09/MAIO/2017 - 
 *
  * Descrição:   Biblioteca adaptada da biblioteca padrão sw_uart.h responsável 
 * pelo funcionamento da comunicação serial UART.
 *****************************************************************************/
#ifndef __UART_H
#define __UART_H

/** I N C L U D E S **********************************************************/
#include "Config.h"

/** D E F I N E S ************************************************************/

// Definição dos pinos de Transmissão(TX) e Recepção(RX) no PIC18F4550
#define PINO_TX	TRISCbits.RC6
#define PINO_RX	TRISCbits.RC7

/**  P R O T O T I P O  D E  F U N C O E S  **********************************/

//wilson
char UART_InitBaud(const long int baudrate);
//wilson

/******************************************************************************
 * Funcao:		void UART_Write(char data)
 * Entrada:		(char data) : Caractere que será enviado
 * Saída:		Nenhuma (void)
 * Descrição:	(Envia Um caractere no UART).
 *****************************************************************************/
void UART_Write(char data);


/******************************************************************************
 * Funcao:		char UART_TX_Empty();
 * Entrada:		Nenhuma (void)
 * Saída:		(char)
 * Descrição:	(Verifica o Registro de Transmissão).
 *****************************************************************************/
char UART_TX_Empty();


/******************************************************************************
 * Funcao:		void UART_Write_String(const char *string)
 * Entrada:		*string: Ponteiro que direciona o endereço dos caracteres de uma string
 * Saída:		Nenhuma (void)
 * Descrição:	Envia uma string na comunicação UART.
 *****************************************************************************/
void UART_Write_String(const char *string);


/******************************************************************************
 * Funcao:		char UART_Data_Ready();
 * Entrada:		Nenhuma (void)
 * Saída:		(char)
 * Descrição:	(Verifica se os dados estão prontos para a leitura)
 * Utiliza o bit de sinalização(Flag) RCIF que será definido quando a recepção
 * de dados for concluída.
 *****************************************************************************/
char UART_Data_Ready();


/******************************************************************************
 * Funcao:		char UART_Read()
 * Entrada:		Nenhuma (void)
 * Saída:		(char)
 * Descrição:	Essa rotina espera até que a recepção esteja completa e em seguida
 * lê os dados de "8 bits" do registrador RCREG.
 *****************************************************************************/
char UART_Read(void);


/******************************************************************************
 * Funcao:		void UART_Read_String(char *buffer, unsigned int length)
 * Entrada:		char *buffer: Ponteiro que direciona para os endereços dos caracteres
 *                            da string recebida.
 *              unsigned int length: Tamanho da string que foi recebida.
 * Saída:	    Nenhuma (void)
 * Descrição:	Essa rotina lê uma string a partir do endereço do primeiro caractere
 *              e de seu tamanho.
 *****************************************************************************/
void UART_Read_String(char *buffer, unsigned char length);


/******************************************************************************
 * Funcao:		void UART_Write_INT(int valor)
 * Entrada:		int valor: tipo inteiro sinalizado.
 * Saída:	    Nenhuma (void)
 * Descrição:	Essa rotina envia um valor tipo signed int (de -32768 a 32767)
 *  pela comunicação UART, Sendo que este valor é convertido para Unsigned char .
 *****************************************************************************/
void UART_Write_INT(int valor);

/******************************************************************************
 * Funcao:		void Init_UART(void)
 * Entrada:		Nenhuma.
 * Saída:	    Nenhuma (void)
 * Descrição:	Essa função inicializa o periferico UART.
 *****************************************************************************/
void Init_UART(void);

/*********************************FIM****************************************/

#endif
