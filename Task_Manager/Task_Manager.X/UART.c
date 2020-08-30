/******************************************************************************
 * Nome do Arquivo: UART.c
 * 
 * Processador:	PIC18F4550
 * Opção de Clock:	HS 20MHz (externo) - CPU: 48MHz
 * Compilador:	C18 
 *
 * Autor:                   Weslley M. Torres
 *
 * Data:		v1 - 09/Maio/2017 - 
 *
 * Descrição:              Biblioteca responsável pelo funcionamento da comunicação
 *                                serial UART.
 *****************************************************************************/

/** I N C L U D E S **********************************************************/
#include "Config.h"
#include <stdlib.h>
#include "UART.h"

/** PROTOTIPOS DE FUNCOES ****************************************************/
 
 char UART_InitBaud(const long int baudrate);
 
/** F U N C O E S ************************************************************/

/******************************************************************************
 * Funcao:          char UART_InitBaud(const long int baudrate)
 * Entrada:          (const long int baudrate)
 * Saída:              (char UART_InitBaud)
 * Descrição:       Configura alguns registradore do PIC 18F4550 referentes 
 *                         a comunicação UART. Configura os parametros de comunicação tais com:
 *                         - modo de operação
 *                         - Taxa de transferência
 *                         Ao final retorna (1) caso tenha sucesso na inicialização, ou (0) se houver falha na inicialização.
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
        SPEN =  1;
        PINO_RX = 1;
        PINO_TX = 1;
        CREN =  1;
        TXEN =  1;
        return (1);
    }
    return (0);	
} // Fim UART_Init

/******************************************************************************
 * Funcao:		void UART_Write(char data)
 * Entrada:		(char data) : Caractere que será enviado
 * Saída:		Nenhuma (void)
 * Descrição:             (Envia Um caractere no UART).
 *****************************************************************************/
void UART_Write(char data)
{
    while(!PIR1bits.TXIF);
    TXREG = data;
} // Fim UART_Write

/******************************************************************************
 * Funcao:		char UART_TX_Empty();
 * Entrada:		Nenhuma (void)
 * Saída:		(char)
 * Descrição:             (Verifica o Registro de Transmissão).
 *****************************************************************************/
char UART_TX_Empty()
{
    return (TRMT);
} // Fim UART_TX_Empty

/******************************************************************************
 * Funcao:		void UART_Write_String(const char *string)
 * Entrada:		*string: Ponteiro que direciona o endereço dos caracteres de uma string
 * Saída:		Nenhuma (void)
 * Descrição:             Envia uma string na comunicação UART.
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
 * Saída:		(char)
 * Descrição:             (Verifica se os dados estão prontos para a leitura)
 *                               Utiliza o bit de sinalização(Flag) RCIF que será definido quando a recepção
 *                               de dados for concluída.
 *****************************************************************************/
char UART_Data_Ready()
{
    return (RCIF);
} // Fim UART_Data_Ready

/******************************************************************************
 * Funcao:		char UART_Read()
 * Entrada:		Nenhuma (void)
 * Saída:		(char)
 * Descrição:             Essa rotina espera até que a recepção esteja completa e em seguida
 *                               lê os dados de "8 bits" do registrador RCREG.
 *****************************************************************************/
char UART_Read(void)
{
    while (!PIR1bits.RCIF);
    return (RCREG);
} // Fim UART_Read

/******************************************************************************
 * Funcao:		void UART_Read_String(char *buffer, unsigned int length)
 * Entrada:		char *buffer: Ponteiro que direciona para os endereços dos caracteres
 *                               da string recebida.
 *                               unsigned int length: Tamanho da string que foi recebida.
 * Saída:                    Nenhuma (void)
 * Descrição:             Essa rotina lê uma string a partir do endereço do primeiro caractere
 *                               e de seu tamanho.
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
 * Funcao:          void UART_Write_INT(int valor)
 * Entrada:         int valor: tipo inteiro sinalizado.
 * Saída:             Nenhuma (void)
 * Descrição:      Essa rotina envia um valor tipo signed int (de -32768 a 32767)
 *                        pela comunicação UART, Sendo que este valor é convertido para Unsigned char .
 *****************************************************************************/

void UART_Write_INT(int valor)
{
    unsigned char valor_final[7] = "000000";
    itoa(valor_final,valor, 10); 
    UART_Write_String(valor_final);  //Escreve o valor já convertido
    UART_Write_String("\r\n");       //Quebra de linha  
} // Fim UART_Write_INT

/******************************************************************************
 * Funcao:          void Init_UART(void)
 * Entrada:         Nenhuma.
 * Saída:             Nenhuma (void)
 * Descrição:      Essa função inicializa o periferico UART.
 *****************************************************************************/
void Init_UART(void)
{
    PINO_TX    = 0; 				// Registrador responsavel pelo envio de dados via UART.
    PINO_RX    = 0; 				// Registrador responsavel pelo recebimento de dados via UART.
    (void)UART_InitBaud(9600);                // Inicializa Comunicação UART.
}
/*********************************FIM****************************************/