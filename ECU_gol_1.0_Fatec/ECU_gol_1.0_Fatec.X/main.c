/*
 * File:    (main.c) ECU MONOPONTO - FATEC SANTO ANDRE
 * Processor:   PIC18f4550
 * Conpiler:    MPLAB X v3.65 + XC8 v1.45
 * Company: FATEC Santo Andre
 * Author:  Prof. Edson Kitani
 * Date:  12/02/2019
 *
 * Software License Agreement: Somente para fins didaticos
 * 
 ********************************************************************************
 * File Description: 
 * Este programa funciona como uma ECU de EFI Monoponto para o
 * veiculo GOl.
 * Esta versao e usada no Lab para teste das placas.
 * Change History
 * 1.0 29/08/2019 
 * 2020 update: wilson Queiroz de Oliveira
 */

#include "config.h"

//Define algumas variaveis globais

unsigned long int    tick_time=0;     //Gera contador de tempo
unsigned long int    t_RPM = 0;      //Contador de intervalo de tempo da RPM
unsigned long int    t_MAP = 0;      //Contador de intervalo da freq. do MAP
unsigned long int    f_RPM = 0;      //Valor calculado da freq. de RPM
long int                   f_MAP = 0;      //Valor calculado da freq. de MAP
unsigned long int    rotacao = 0;      //Rotacao do motor
unsigned long int    t100_ms = 0;    //Contador de tempo de 100ms.

unsigned long int    TPS_atual = 0;           //Media dos valores atuais do TPS
unsigned int            TPS_ant = 0;              //Valor anterior do TPS
unsigned int            ACC = 0;                   //Valor da bomba de aceleracao
unsigned long         ACT = 0;                    //Media dos valores da temperatura do ar
unsigned int            FF_Borda = 0;           //Flip flop para mundaca de borda
unsigned int            Conta_PIP = 0;          //Flip flop para saltar dois PIPs
unsigned int            T_inj = 0;                   //Tempo de injecao
unsigned int            tinj = 100;                  //Tempo de injecao para o display
unsigned int            entrada_AN0 = 0;      //Valor binario da entrada AN0
unsigned int            loop_AN0 = 0;           //Contador de leitura do AN0
unsigned int            somatorio_AN0 = 0;  //Somatorio dos valores do AN0
unsigned int            entrada_AN1 = 0;      //Valor binario da entrada AN1
unsigned int            loop_AN1 = 0;           //Contador de leitura AN1
unsigned int            somatorio_AN1 = 0;  //Somatorio dos valores de AN1




//------------------------------------------------------------------------------
// // Define e gerencia interrupcoes de Timer_0, INT_EX0, INT_EX1

void interrupt high_priority interupcoes(void)
{
    if (INTCONbits.TMR0IF == 1) //Esta interrupcao ocorre a cada 0,1 ms
    {

        ADCON0bits.CHS = 00;       //Ativa leitura do AN0
        ADCON0bits.GO  = 1;

        INTCONbits.TMR0IF = 0;    //Reset o flag para a proxima interrupcao
        
        tick_time++;     //Acumula o numero de interrupcoes para usar como delay
        t_RPM++;        //Contador para calcular rotacao do motor
        t_MAP++;        //Contador para calcular frequencia do MAP
        tinj--;                 //Decrementa o tempo de injecao
        t100_ms--;        //Decrementa o contador de 100ms

        Ocilador = !Ocilador;

        if (tinj>80)    //Limita o tempo de injecao em 8,0 ms
        {
            tinj=80;
        }
        if (tinj<=0)
        {
            tinj=0;
            Saida_Bico = 0;
        }

        //------------------------------------------------------------------------------
        // entrada analogica AN1 - Sinal do TPS

        __delay_us(20);
        
        if(ADCON0bits.GO_DONE == 0)
        {
            entrada_AN0 = (ADRESH<<8) + ADRESL;  //Monta uma word
            loop_AN0++;
            somatorio_AN0 = somatorio_AN0 + entrada_AN0;

            if (loop_AN0 > 7)   //Acumula 10 medidas
            {
                TPS_atual = somatorio_AN0 >> 3; //Media das 8 medidas
                loop_AN0 = 0;
                somatorio_AN0 = 0;
            }
        }

        //-----------------------------------------------------------------------------
        //entrada analógica AN0 - Sinal do ACT

        ADCON0bits.CHS = 01; //Ativa leitura AN1
        ADCON0bits.GO  = 1;

        __delay_us(20);
        if (ADCON0bits.GO_DONE == 0)
        {
            entrada_AN1 = (ADRESH<<8) + ADRESL; //Monta uma word
            loop_AN1++;
            somatorio_AN1 = somatorio_AN1 + entrada_AN1;

            if (loop_AN1 > 7)          //Acumula 10 medidas
            {
                ACT = somatorio_AN1 >> 3;       //Media das 8 medidas
                loop_AN1 = 0;
                somatorio_AN1 = 0;
            }
        }

    // ----------------------------------------------------------------------------
    //As linhas abaixo serao executadas a cada 100ms
    //Detecta a derivada do TPS

    if (t100_ms <= 0)                   //Interrupcao a cada 100ms
    {
        if (TPS_atual > TPS_ant)
        {
            ACC = TPS_atual - TPS_ant;
        }
        
        TPS_ant = TPS_atual;
        t100_ms = 1000;                 //Recarrega o temporizador
    }

    if (TPS_atual <= 6)
    {
        TPS_atual = 6;                  //controla tempo minimo TPS
    }
    //----------------------------------------------------------------------------/

    TMR0L = 108 + TMR0L;     //Valor do estouro + residuo para 100us

    /* 
     * Com 220 a frequencia de 20,13563 kHz (24,83 us por interrupcao)
     * Com 183 a frequencia de 9,967474 kHz (50,16 us por interrupcao)
     * Com 107 a frequencia de 4,992028 kHz (100,2 us por interrupcao)
     */

    }

    //-----------------------------------------------------------------------------
    // Gerencia Interrupcao Externa 0 do sinal de Rotacao via PIP

    if (INT0IE && INT0IF)
    {
        INT0IF = 0;     //Libera interrupcao
        
        //se a 100 < rotacaso < 600, injeta na borda de descida

        if ((rotacao>100)&&(rotacao<600)&&(FF_Borda==0))
        {
            Saida_Bico = 1;     //Liga o bico injetor
            T_inj      = 40;    //carrega o tempo de injecao 4 ms
            tinj       = T_inj; //coloca no buffer do display
            Conta_PIP  = 0;
        }
        else
        {   
            //Se a rotaçao > 450, injeta na borda de subida a cada dois pulsos
            if ((rotacao>450)&&(FF_Borda==1)&&(Conta_PIP>2))        
            {
                Saida_Bico = 1;     //Liga o bico injetor
                T_inj = 26;             //carrega o tempo de injeçao
                tinj = T_inj;           //coloca no buffer do display
                Conta_PIP  = 0;
            }
            else
            {
                Conta_PIP++;        //Incrementa contador de PIP
            }           
        }
        if (FF_Borda == 1)
        {
            f_RPM=t_RPM;            //Atualiza rotacao no display
            t_RPM = 0;                    //Zera contador de tempo da rotacao
        }
        if (FF_Borda == 0)
        {
            INTCON2bits.INTEDG0=1;  //liga interrupcao na borda de subida
            FF_Borda = 1;
        }
        else
        {
            INTCON2bits.INTEDG0=0;  //liga interrupcao na borda de descida
            FF_Borda = 0;
        }
    }

    //-----------------------------------------------------------------------------
    // Gerencia Interrupcao Externa 1 do sinal de MAP

    if ((INT1IE && INT1IF))
    {
        INT1IF= 0;               //Libera interrupcao

        f_MAP = t_MAP;                //Carrega a contagem de pulso entra bordas
        t_MAP = 0;                          //Zera contador
        f_MAP = 10000/f_MAP;    //Apenas converte para frequencia
    }   
}

// tabela a ser interpolada do sensor ACT
typedef struct 
{ 
    signed long x; 
    signed long y; 
} coord_t; // map act

coord_t c[6] = 
{
    {102.4,100.0},  //  102   100
    {122.88,90.0},  //  122   90
    {163.84,80.0},  //  163   80
    {266.24,60.0},  //  266   60
    {430.08,40.0},  //  430   40
    {634.88,20.0}   //  634   20
};    


// Interpolacao
signed long interp( coord_t* c, signed long x, int n )
{
    int i;

    for( i = 0; i < n-1; i++ )
    {
        if ( c[i].x <= x && c[i+1].x >= x )
        {
            signed long diffx = x - c[i].x;
            signed long diffn = c[i+1].x - c[i].x;

            return c[i].y + ( c[i+1].y - c[i].y ) * diffx / diffn; 
        }
    }

    return 0; // Not in Range
}
//*****************************************************************************
//                              PROGRAMA PRINCIPAL
//*****************************************************************************



int main(int argc, char** argv) 
{

//Texto das Telas

const unsigned char Texto_0[] = "Injecao do GOL  ";
const unsigned char Texto_1[] = "Digit. Wilson.Q ";
const unsigned char Texto_2[] = "RPM=    ACT=    ";
const unsigned char Texto_3[] = "TPS=    INJ=    ";
const unsigned char Texto_4[] = "RPM=    MAP=    ";
const unsigned char Texto_5[] = "TPS=    ACC=    ";

//Define as variaveis do Programa Principal

int FF_Borda = 0;   //Flip flop para detectar botao solto
int FF_Pagina = 0;   //Flip flop de mudanca de pagina

//Define as funcoes dos pinos e inicializa os buffers de saida

LATA = 0X00;
LATB = 0XFF;    // Carrega FF para apagar os LEDs
LATC = 0X00;
LATD = 0X00;
LATE = 0X00;

TRISB = 0X03;           // Define PORTB como saidas e entradas de interrupcao
TRISE = 0XFF;           // Define como entradas (Botoes)
TRISC = 0X00;           // Define como saÃ­das
//TRISD = 0X00;
TRISAbits.TRISA0 = 1;   // Entrada para AN0
TRISAbits.TRISA1 = 1;   // Entrada para AN1
//-----------------------------------------------------------------------------------
// Configura a entrada AN0 e AN1 e todas as outras do byte RA para digital
// Ver tabela da pÃ¡gina 260 do Manual do PIC 18F4550 pra outras configuracoes

ADCON1bits.PCFG3 = 1;
ADCON1bits.PCFG2 = 1;
ADCON1bits.PCFG1 = 0;
ADCON1bits.PCFG0 = 1;

// ADC Setup
// Ver tabela da pagina 261 do Manual do PIC 18F4550

ADCON2bits.ADFM = 1;    //Ajusta justificacao para direita
ADCON1bits.VCFG0 = 0;   //Referencia VDD
ADCON1bits.VCFG1 = 0;   //Referencia VSS

ADCON2bits.ADCS0 = 0;   //Seleciona divisor FOSC/64
ADCON2bits.ADCS1 = 1;
ADCON2bits.ADCS2 = 1;

ADCON2bits.ACQT0 = 1;   //Seleciona tempo de aquisicao (2,66 us)
ADCON2bits.ACQT1 = 0;
ADCON2bits.ACQT2 = 0;
ADCON0bits.ADON = 1;    //Ativar modulo de ADC

ADCON0bits.CHS0 = 0;    //Selecina AN0 para ligar no S/H
ADCON0bits.CHS1 = 0;
ADCON0bits.CHS2 = 0;
ADCON0bits.CHS3 = 0;

// Configurar timer 0 (consulte o manual do PIC 18F4550 na pagina 125)
// Lembre-se que o clock de 48MHz quando se trabalha com USB

T0CONbits.TMR0ON = 1;   // Habilitar o timer 0
T0CONbits.T08BIT = 1;   // Habilitar no modo 8bits
T0CONbits.T0CS   = 0;   // Usa o oscilador interno como clock;
T0CONbits.T0SE   = 0;   // Irrelevamte na selecao interna
T0CONbits.PSA    = 0;   // Ativa o Prescaler para dividir o sinal do clock
T0CONbits.T0PS   = 0b010;   // Prescaler divisor por 8

// Carrega o valor inicial no registrador baixo do timer 0

TMR0L = 107;    // Valor do estouro

// Configura a Interrupcao do timer 0

INTCONbits.TMR0IE = 1;  // Habilita Timer 0 pelo flag de overflow

//Habilita interrupcao externa 0 e 1
//Pino B0 e B1 sao entrada e pinos B[2-7] sao saidas

INTCONbits.RBIE = 0;
INTCONbits.INT0IE = 1;
INTCON3bits.INT1IE=1;
INTCONbits.GIE=1;

//Inicializa display e faz saudacao

ConfiguraLCD();
PosicaoCursorLCD(1,1);
EscreveFraseRamLCD(Texto_0);
PosicaoCursorLCD(2,1);
EscreveFraseRamLCD(Texto_1);
DesligaCursor();
delay_ms(1000);
LimpaDisplay();
PosicaoCursorLCD(1,1);
EscreveFraseRamLCD(Texto_4);
PosicaoCursorLCD(2,1);
EscreveFraseRamLCD(Texto_5);

while (1)
{
    if(Botao_B1==0 && FF_Borda==0)  //Avalia borda de descida do botao
        {
            FF_Borda=1;                 //Memoriza que botao foi precionado
            if (FF_Pagina==0)
            {
                PosicaoCursorLCD(1,1);
                EscreveFraseRamLCD(Texto_2);
                PosicaoCursorLCD(2,1);
                EscreveFraseRamLCD(Texto_3);
                FF_Pagina = 1; //Memoriza que o botao foi acionado
            }
            else
            {
                if (FF_Pagina == 1)
                {
                    PosicaoCursorLCD(1,1);
                    EscreveFraseRamLCD(Texto_4);
                    PosicaoCursorLCD(2,1);
                    EscreveFraseRamLCD(Texto_5);
                    FF_Pagina = 0;      // Flag de apoio para detecao de borda
                }   
            }
        }
        else
        {
            if (Botao_B1==1 && FF_Borda==1) //Muda de pagina
            {
                FF_Borda=0;
            }
        }

        delay_ms(100);
        PosicaoCursorLCD(2,5);
        EscreveFraseRamLCD("    ");
        PosicaoCursorLCD(2,5);
        EscreveInteiroLCD(((TPS_atual*100)/1024));
        rotacao = f_RPM/10;
        rotacao = 30000/rotacao;
        PosicaoCursorLCD(1,5);
        EscreveFraseRamLCD("    ");
        PosicaoCursorLCD(1,5);
        EscreveInteiroLCD(rotacao);

        if (FF_Pagina==0)
        {
            PosicaoCursorLCD(2,13);
            EscreveFraseRamLCD("    ");
            PosicaoCursorLCD(2,13);
            EscreveInteiroLCD(ACC);
            PosicaoCursorLCD(1,13);
            EscreveFraseRamLCD("   P");
            PosicaoCursorLCD(1,13);
            f_MAP = (((((f_MAP-80)*-1)+80)*101)/80); //Pa
            EscreveInteiroLCD(f_MAP);
        }
        else
        {
            PosicaoCursorLCD(1,13);
            EscreveFraseRamLCD("   C");
            
            PosicaoCursorLCD(1,13);
            //EscreveInteiroLCD((((ACT*(-1))+1024)*120)/1024); //C
            
            //long int y = interp( c, ACT, 6 );
            unsigned int y =interp( c, ACT, 6 );
            EscreveInteiroLCD(y); //C
            
            PosicaoCursorLCD(2,13);
            EscreveFraseRamLCD("  ms");
            
            PosicaoCursorLCD(2,13);
            EscreveFloatLCD((tinj/10),0); //ms
            //EscreveInteiroLCD((tinj));

        }
    }
}

