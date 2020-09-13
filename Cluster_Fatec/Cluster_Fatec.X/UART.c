/******************************************************************************
 * Nome do Arquivo:	UART.c
 * Dependencias:	Veja arquivo "UART.h"
 * Processador:		PIC18F4550
 * Op��o de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:		C18 
 *
 * Autor:			
 *
 * Data:			v1 - 09/Maio/2017 - 
 *
 * Descri��o:   Biblioteca respons�vel pelo funcionamento da comunica��o
 * serial UART.
 *****************************************************************************/


/** I N C L U D E S **********************************************************/
#include "Config.h"
#include <stdlib.h>
#include "UART.h"


/** PROTOTIPOS DE FUNCOES ****************************************************/
 
// char UART_InitBaud(const long int baudrate);
 
/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:		char UART_InitBaud(const long int baudrate)
 * Entrada:	   (const long int baudrate)
 * Sa�da:	   (char UART_InitBaud)
 * Descri��o:	Configura alguns registradore do PIC 18F4550 referentes 
 *	a comunica��o UART. Configura os parametros de comunica��o tais com:
 *	- modo de opera��o
 *	- Taxa de transfer�ncia
 *	Ao final retorna (1) caso tenha sucesso na inicializa��o, ou (0) se houver falha na inicializa��o.
 *****************************************************************************/
char UART_InitBaud(const long int baudrate)
{
    unsigned int x;
    
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
    if(x > 255)
    {
        x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
        BRGH = 1;
    }
    if(x < 256)
    {
        SPBRG = x;
        SYNC =  0;
        SPEN =  1;//wilson
        RCIE  =  1;//wilson
//        PINO_RX = 1;
//        PINO_TX = 1;
        CREN =  1;
        TXEN =  1;
        WUE = 1;//wilson
        
        return (1);
    }
    return (0);
	
} // Fim UART_Init


/******************************************************************************
 * Funcao:		void UART_Write(char data)
 * Entrada:		(char data) : Caractere que ser� enviado
 * Sa�da:		Nenhuma (void)
 * Descri��o:	(Envia Um caractere no UART).
 *****************************************************************************/
void UART_Write(char data)
{
    while(!PIR1bits.TXIF);
    TXREG = data;
} // Fim UART_Write


/******************************************************************************
 * Funcao:		char UART_TX_Empty();
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:	(Verifica o Registro de Transmiss�o).
 *****************************************************************************/
char UART_TX_Empty()
{
    return ((unsigned char)TRMT);
} // Fim UART_TX_Empty


/******************************************************************************
 * Funcao:		void UART_Write_String(const char *string)
 * Entrada:		*string: Ponteiro que direciona o endere�o dos caracteres de uma string
 * Sa�da:		Nenhuma (void)
 * Descri��o:	Envia uma string na comunica��o UART.
 *****************************************************************************/
void UART_Write_String(const char *string)
{
    while(*string)
    {
        UART_Write(*string++);
    }
} // Fim UART_Write_String


/******************************************************************************
 * Funcao:		char UART_Data_Ready();
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:	(Verifica se os dados est�o prontos para a leitura)
 * Utiliza o bit de sinaliza��o(Flag) RCIF que ser� definido quando a recep��o
 * de dados for conclu�da.
 *****************************************************************************/
char UART_Data_Ready()
{
    return ((unsigned char)RCIF);
} // Fim UART_Data_Ready


/******************************************************************************
 * Funcao:		char UART_Read()
 * Entrada:		Nenhuma (void)
 * Sa�da:		(char)
 * Descri��o:	Essa rotina espera at� que a recep��o esteja completa e em seguida
 * l� os dados de "8 bits" do registrador RCREG.
 *****************************************************************************/
char UART_Read(void)
{
    while (!PIR1bits.RCIF);
    
    return (RCREG);
} // Fim UART_Read



/******************************************************************************
 * Funcao:		void UART_Read_String(char *buffer, unsigned int length)
 * Entrada:		char *buffer: Ponteiro que direciona para os endere�os dos caracteres
 *                            da string recebida.
 *              unsigned int length: Tamanho da string que foi recebida.
 * Sa�da:	    Nenhuma (void)
 * Descri��o:	Essa rotina l� uma string a partir do endere�o do primeiro caractere
 *              e de seu tamanho.
 *****************************************************************************/
void UART_Read_String(char *buffer, unsigned char length)
{
    unsigned int i;
    char aux;
    for(i = 0; i < length; i++)
    {
        aux = UART_Read();
        
        if(aux == 0x0D)
        {
            for(i; i < length; i++)
            {
              buffer[i] = ' ';
            }
            break;
        }
        buffer[i] = aux;
        
    }
} // Fim UART_Read_String


/******************************************************************************
 * Funcao:		void UART_Write_INT(int valor)
 * Entrada:		int valor: tipo inteiro sinalizado.
 * Sa�da:	    Nenhuma (void)
 * Descri��o:	Essa rotina envia um valor tipo signed int (de -32768 a 32767)
 *  pela comunica��o UART, Sendo que este valor � convertido para Unsigned char .
 *****************************************************************************/
void UART_Write_INT(int valor)
{
    unsigned char valor_final[7] = "000000";
    
    itoa(valor_final,valor, 10); 
    UART_Write_String(valor_final);  //Escreve o valor j� convertido
    UART_Write_String("\r\n");       //Quebra de linha
    
} // Fim UART_Write_INT

/******************************************************************************
 * Funcao:		void Init_UART(void)
 * Entrada:		Nenhuma.
 * Sa�da:	    Nenhuma (void)
 * Descri��o:	Essa fun��o inicializa o periferico UART.
 *****************************************************************************/
void Init_UART(void)
{
    //wilson
    PINO_TX    = 1; 				// Registrador responsavel pelo envio de dados via UART.
    PINO_RX    = 1; 				// Registrador responsavel pelo recebimento de dados via UART.
    
//    PINO_TX    = 0; 				// Registrador responsavel pelo envio de dados via UART.
//    PINO_RX    = 0; 				// Registrador responsavel pelo recebimento de dados via UART.
	
	(void)UART_InitBaud(9600);                // Inicializa Comunica��o UART.
}

/*********************************FIM****************************************/
