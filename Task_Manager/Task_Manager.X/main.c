/*
 * MainTaskMng.c
 * Author: Pedro Bertoleti
 * Data: Jan/2016
 * Description: 
 * This software is a task manager for 8-bit PIC microcontrollers.
 * WARNING: be careful when programming the tasks. Tasks must be as fast as possible (due to real-time features of this task manager)
 */

/* Changed by Weslley Torres in order to fit into hardware developed on FATEC Santo André	*/
/* Author: Weslley Torres																	*/
/* Date: 08/May/ 2016																		*/

/* Changed by  Wilson Queiroz; Jackson;   Juliano; in order to fit into hardware developed automotive display   */
/* Author:  Jackson;   Juliano;  Wilson Queiroz;                                                               */
/* Date: 30/May/ 2019                                                                       */

//#include "Config.h"
#include "Hardware.h"
#include "displayLCD.h"
#include "I2C_SW.h"
#include "ADC.h"
#include "SHRC.h"
#include <stdio.h>
#include "UART.h"
/************************************************************************************************/
/* 											Variables		 									*/
/************************************************************************************************/
/*Store function pointers of Task.*/
void (*ScheduledTasks[NUMBER_OF_TASKS])(void);  

/*Store task´s times (time period to execute)*/
int TimeScheduledTasks[NUMBER_OF_TASKS];       
 
/*Stores recent task´s times ("time to execute" each task) */
int RecentTasksTimeToExecute[NUMBER_OF_TASKS];  

/*Tells if TImer0 interrupt has been generated*/
char Timer0IntGeneraed = 0;                        
 
/* Tells if a task in executing (used to check task timeout validation)*/
volatile char TaskIsExecuting;                  

int TaskTimeout;

uint8_t TimerBreathingLight = 100;
uint8_t Tecla_lida = 0;

uint8_t FlagDeb = 0;
uint8_t TensaoADC = 0;

// variaveis wilson
unsigned char N_funcao = 8;  //ESCOLHE FUNÇÃO
unsigned char Contagem = 0;  //ESCOLHE FUNÇÃO

unsigned char Code;          //UART
unsigned char botao2 = 0;
unsigned char Contagem2 = 0;  //conta botao 2

/************************************************************************************************/
/* 											Function Prototipe 									*/
/************************************************************************************************/

void ConfigTimer0(void);
void InitTasks(void);
void ExecuteTask(void);
void Init_Ports(void);

void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task5(void);
void Task6(void);
void Task7(void);
void Task8(void);

//funções wilson
void EscreveLEDs();

/*************************************************************************************************/

/**
 *  \brief Initialize and schedule tasks
 *  
 *  \return none
 *  
 *  \details Initialize the scheduller
 */
void InitTasks(void)
{
    //init function pointers of tasks
    ScheduledTasks[INDEX_TAREFA_1] = Task1;
    ScheduledTasks[INDEX_TAREFA_2] = Task2;
    ScheduledTasks[INDEX_TAREFA_3] = Task3;
    ScheduledTasks[INDEX_TAREFA_4] = Task4;
    ScheduledTasks[INDEX_TAREFA_5] = Task5;
    ScheduledTasks[INDEX_TAREFA_6] = Task6;
    ScheduledTasks[INDEX_TAREFA_7] = Task7;
    ScheduledTasks[INDEX_TAREFA_8] = Task8;

    /*init temporization values of each task. These values do no 
    change during execution*/
    TimeScheduledTasks[INDEX_TAREFA_1] = TIME_TO_EXECUTE_TASK1;
    TimeScheduledTasks[INDEX_TAREFA_2] = TIME_TO_EXECUTE_TASK2;
    TimeScheduledTasks[INDEX_TAREFA_3] = TIME_TO_EXECUTE_TASK3;
    TimeScheduledTasks[INDEX_TAREFA_4] = TIME_TO_EXECUTE_TASK4;
    TimeScheduledTasks[INDEX_TAREFA_5] = TIME_TO_EXECUTE_TASK5;
    TimeScheduledTasks[INDEX_TAREFA_6] = TIME_TO_EXECUTE_TASK6;
    TimeScheduledTasks[INDEX_TAREFA_7] = TIME_TO_EXECUTE_TASK7;
    TimeScheduledTasks[INDEX_TAREFA_8] = TIME_TO_EXECUTE_TASK8;
	
    /*init recent temporization values of each task. These values will 
    change during execution (they´re used to decide which task must be executed)*/

    RecentTasksTimeToExecute[INDEX_TAREFA_1] = TIME_TO_EXECUTE_TASK1;
    RecentTasksTimeToExecute[INDEX_TAREFA_2] = TIME_TO_EXECUTE_TASK2;
    RecentTasksTimeToExecute[INDEX_TAREFA_3] = TIME_TO_EXECUTE_TASK3;	
    RecentTasksTimeToExecute[INDEX_TAREFA_4] = TIME_TO_EXECUTE_TASK4;
    RecentTasksTimeToExecute[INDEX_TAREFA_5] = TIME_TO_EXECUTE_TASK5;
    RecentTasksTimeToExecute[INDEX_TAREFA_6] = TIME_TO_EXECUTE_TASK6;	
    RecentTasksTimeToExecute[INDEX_TAREFA_7] = TIME_TO_EXECUTE_TASK7;
    RecentTasksTimeToExecute[INDEX_TAREFA_8] = TIME_TO_EXECUTE_TASK8;
    //It indicates that there´s no task executing
    TaskIsExecuting = NO;
}

/**
 *  \brief ExecuteTask
 *  
 *  \return none
 *  
 *  \details Execute tasks assigned to the system
 */
void ExecuteTask(void)
{
    char i;
    for (i=0; i<NUMBER_OF_TASKS; i++)
    {
        //Check if it´s time to execute a task
        if ((ScheduledTasks[i] != 0) && (RecentTasksTimeToExecute[i] == 0))
        {
            TaskIsExecuting = YES;
            TaskTimeout = TASK_TIMEOUT;
            ScheduledTasks[i]();  //executes the task
            TaskIsExecuting = NO;
            RecentTasksTimeToExecute[i] = TimeScheduledTasks[i];  //reagendamento da tarefa
        }
    }
}


/**
 *  \brief Task1
 *  
 *  \return none
 *  
 *  \details Executes task 1
 */
void Task1(void)
{
    if(N_funcao==1)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("1");
        
        PosicaoCursorLCD(1,2);
        EscreveFraseRamLCD("Leds");
        PosicaoCursorLCD(2,4);
        EscreveFraseRamLCD("Aleatorios");
        
        __delay_ms(100);
        
        static uint8_t SHRC_Info = 0;
        static uint8_t c =0;

        uint8_t Matriz[16] = {"wilson"};
            
        SHRC_Controle(Matriz [c]);
   
        if(c >= 15)
            {
                c=0;
            }
        c++;       
    }
    LATBbits.LATB0 = ~LATBbits.LATB0;
}
//task2 escreve EEPROM
void Task2(void)
{
    if(N_funcao==2)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("2");
        PosicaoCursorLCD(1,2);
        EscreveFraseRamLCD("B2 White EEPROM");

        static uint8_t data1Error, data2Error;
        static uint8_t ValorA = 0;
        static uint8_t ValorB = 10;
        static uint8_t str2;
        
        if (botao2 == 1)
        {
            data1Error = write_eeprom_byte(0x10, ValorA);
                                    //                                  |     |----> Dado a ser escrito na EEPROM
                                    //                                  |----------> Endereco na EEPROM
            data2Error = write_eeprom_byte(0x11, ValorB);
                                    //                                  |     |----> Dado a ser escrito na EEPROM
                                    //                                  |----------> Endereco na EEPROM    
            botao2 = 0;     // somente uma escrita na EEPROM
                        
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD("Valor A,B:");
            
            PosicaoCursorLCD(2,11);
            sprintf( str2, "%d", ValorA);//coverte ival para string
            EscreveFraseRamLCD(str2);

            PosicaoCursorLCD(2,13);
            EscreveFraseRamLCD(",");

            PosicaoCursorLCD(2,14);
            sprintf( str2, "%d", ValorB);//coverte ifval para string
            EscreveFraseRamLCD(str2);
            
            ValorA++;
            ValorB++;
        }
    }
    LATBbits.LATB1 = ~LATBbits.LATB1;
}
// imprime no lcd a memoria EEPROM
void Task3(void)
{
    if(N_funcao==3)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("3");

        static uint8_t Escrever = 0;
        uint8_t MsgPrimLinhaTask3[17] = "End. 0x10 = ";
        uint8_t MsgSegLinhaTask3[17]  = "End. 0x11 = ";

        uint8_t DadoLido1, DadoLido2;

        /* Write welcome screen on LCD line 1 */
        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD(MsgPrimLinhaTask3);

        /* Write welcome screen on LCD line 2 */
        PosicaoCursorLCD(2,1);
        EscreveFraseRamLCD(MsgSegLinhaTask3);

        DadoLido1 = read_eeprom_byte(0x10);
        //                                  |----------> Endereco na EEPROM
        DadoLido2 = read_eeprom_byte(0x11);
        //                                  |----------> Endereco na EEPROM
        
        PosicaoCursorLCD(1,13);
        EscreveInteiroLCD(DadoLido1);

        PosicaoCursorLCD(2,13);
        EscreveInteiroLCD(DadoLido2);
        //A linha abaixo funciona somente como um aviso que a task esta "rodando"
    }
    LATBbits.LATB2 = ~LATBbits.LATB2;  
}

// fucao ADC
void Task4(void)
{
    if(N_funcao==4)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("4");
        /* Armazena leitura do conversor AD */

        static float canal_0 = 0.100;
        static float canal_1 = 0.100;

        static float read = 0.100;

        static uint8_t str;

        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD("canal_0 :");
        read = adc_read(0);                             //leitura cana 0
        canal_0 = ((read*5.0)/1024.0);           //converte 10bits para decimal
        int ival = (int) canal_0;                        //ival guada inteiro(antes da virgula)
        float fval = canal_0 - ival;                   //fval guarda float(depois da virgula)
        int ifval = (int) 1000*fval;                   //ifval guada a conversao do float para int
                            //((1000*fval)determina numero de casas decimais)
        
        PosicaoCursorLCD(1,11);
        sprintf( str, "%d", ival);          //coverte ival para string
        EscreveFraseRamLCD(str);
        PosicaoCursorLCD(1,12);
        EscreveFraseRamLCD(",");
        PosicaoCursorLCD(1,13);
        sprintf( str, "%d", ifval);         //coverte ifval para string
        EscreveFraseRamLCD(str);

        PosicaoCursorLCD(2,1);
        EscreveFraseRamLCD("canal_1 :");
        read = adc_read(1);                         //leitura cana 1
        canal_1 = ((read*5.0)/1024.0);       //converte 10bits para decimal
        int ival = (int) canal_1;                    //ival guada inteiro(antes da virgula)
        float fval = canal_1 - ival;               //fval guarda float(depois da virgula)
        int ifval = (int) 1000*fval;               //ifval guada a conversao do float para int
                            //((1000*fval)determina numero de casas decimais)
        
        PosicaoCursorLCD(2,11);
        sprintf( str, "%d", ival);          //coverte ival para string
        EscreveFraseRamLCD(str);
        
        PosicaoCursorLCD(2,12);
        EscreveFraseRamLCD(",");
        
        PosicaoCursorLCD(2,13);
        sprintf( str, "%d", ifval);         //coverte ifval para string
        EscreveFraseRamLCD(str);
    }
    LATBbits.LATB3 = ~LATBbits.LATB3;
}
//UART
void Task5(void)
{
    static uint8_t DataTx = 0x20;
    static uint8_t PrimeiraPassagem = 0;
    static uint8_t MsgPrimLinhaTask1[17] = "Dado Rcv";
    
    if(N_funcao==5)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("5");
    
        if(PrimeiraPassagem == 0)
        {
            LimpaDisplay();
            PrimeiraPassagem = 1;
        }

        /* Write welcome screen on LCD line 1 */
        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD(MsgPrimLinhaTask1);

        /* Write welcome screen on LCD line 2 */
        PosicaoCursorLCD(1,12);
        EscreveInteiroLCD(Code);
        EscreveFraseRamLCD("  ");       //vazio para apagar lcd apos fim da transmisão
    }
    UART_Write(DataTx);
    LATBbits.LATB4 = ~LATBbits.LATB4;
}

void Task6(void)
{
    if(N_funcao==6)
        {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("6");
        PosicaoCursorLCD(1,3);
        EscreveFraseRamLCD("Funçao 6");
        PosicaoCursorLCD(2,3);
        EscreveFraseRamLCD("Ler botoes");
        __delay_ms(100);
        }
     
    PosicaoCursorLCD(2,0);          // limpa "B" (B1,B2)
    EscreveFraseRamLCD(" ");    // limpa "B" (B1,B2)
    if (CHAVE_B1 == 0)
        {
            PosicaoCursorLCD(2,0);
            EscreveFraseRamLCD("B");
            Contagem++;
            if ( Contagem >= 10)
            {
                LED_BUZZER = 1;
                __delay_ms(50);
                LED_BUZZER = 0;
                Contagem = 0;
                N_funcao++;
                PosicaoCursorLCD(2,2);
                LimpaDisplay();
            }       
        }
    
    if (CHAVE_B2 == 0)
        {
            PosicaoCursorLCD(2,0);
            EscreveFraseRamLCD("B");
            Contagem2++;
            if ( Contagem2 >= 10)
            {
                LED_BUZZER = 1;
                __delay_ms(50);
                LED_BUZZER = 0;
                Contagem2 = 0;
                botao2 =1;
            }       
        }
    
     if(N_funcao>8)
        {
            N_funcao = 0;
            __delay_ms(100);
        }
    if(0==N_funcao)
    {
        PosicaoCursorLCD(1,2);
        EscreveFraseRamLCD("pressione B1");
        PosicaoCursorLCD(2,2);
        EscreveFraseRamLCD("mudar funcao");
        __delay_ms(100);
    }
    LATBbits.LATB5 = ~LATBbits.LATB5;
}
void Task7(void)
{
    if (N_funcao==7)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("7");
        //        LED_BUZZER = 1;
        //        __delay_ms(1);
        //        LED_BUZZER = 0;
        //        __delay_ms(1);

        static float canal_0 = 0.100;
        static float canal_1 = 0.100;

        static float read = 0.100;

        static char str;
        static char ival;
        static char combustivel;
        static char LEDscombustivel;

        static char bateria;
        static char LEDbateria;

        static unsigned long LEDs;

        unsigned int MASCARA;
        static unsigned int MASCARA32;
        unsigned int i;

        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD("combustivel:");

        read = adc_read(0);                         //leitura cana 0
        canal_0 = ((read*100.0)/1024.0);    //converte 10bits para decimal
        ival = (int) canal_0;                           //ival guada inteiro(antes da virgula)
        combustivel = (int) canal_0;              //ival guada inteiro(antes da virgula)LEDs conbustival

        PosicaoCursorLCD(1,13);
        sprintf( str, "%d", ival);              //coverte ival para string
        EscreveFraseRamLCD(str);
        EscreveFraseRamLCD("%  ");

        PosicaoCursorLCD(2,1);
        EscreveFraseRamLCD("bateria:");

        read = adc_read(1);                         //leitura cana 1
        canal_1 = ((read*14.0)/1024.0);     //converte 10bits para decimal
        ival = (int) canal_1;                           //ival guada inteiro(antes da virgula)
        bateria = (int) canal_1;                    //ival guada inteiro(antes da virgula)LED BATERIA

        PosicaoCursorLCD(2,9);
        sprintf( str, "%d", ival);              //coverte ival para string
        EscreveFraseRamLCD(str);
        EscreveFraseRamLCD("V  ");

        MASCARA32 = 1;
        LEDs = 0x00;

        if (combustivel>10)
        {
            LEDscombustivel = 0b00000001;
        }

        if (combustivel>30)
        {
            LEDscombustivel = 0b00000011;
        }

        if (combustivel>40)
        {
            LEDscombustivel = 0b00000111;
        }

        if (combustivel>60)
        {
            LEDscombustivel = 0b00001111;
        }

        if (combustivel>60)
        {
            LEDscombustivel = 0b00011111;
        }

        if (combustivel>70)
        {
            LEDscombustivel = 0b00111111;
        }

        if (combustivel>80)
        {
            LEDscombustivel = 0b01111111;
        }

        if (combustivel>90)
        {
            LEDscombustivel = 0xff;
        }

        if (combustivel<10)
        {
            LEDscombustivel = 0b00000000;
        }        

        if (bateria<12)
        {
            LEDbateria = 1;
        }
        else
        {
            LEDbateria = 0; 
        }

        LEDs = LEDs + (LEDscombustivel<<8); //0000 0000 1111 1111 0000 0000

        LEDs = LEDs + (LEDbateria<<5);

        //escreveLEDs        
        for(i=0;i<31;i++)
        {
            DADO=(MASCARA&LEDs);
            CLOCK=1;
            __delay_us(1);
            CLOCK=0;
            DADO=0;
            __delay_us(1);
            LEDs=LEDs>>1;
         }
        //exibe leds
        CLOCK=1;                //exibe leds
        ENABLE_RD=1;        //exibe leds
        __delay_us(1);              //exibe leds
        CLOCK=0;                    //exibe leds
        ENABLE_RD=0;            //exibe leds
        __delay_us(1);                  //exibe leds
        //exibe leds
    }
    LATBbits.LATB6 = ~LATBbits.LATB6;
}

void Task8(void)
{
    if(N_funcao==8)
    {
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("8");
        //        LED_BUZZER = 1;
        //        __delay_ms(1);
        //        LED_BUZZER = 0;
        //        __delay_ms(1);
        
        static uint8_t DataTx = 0x20;
        static uint8_t PrimeiraPassagem = 0;
        static uint8_t MsgPrimLinhaTask1[17] = "Dado Rcv";
        static uint8_t uart[9];
        static uint8_t i;
        static uint8_t *buffer;
        
        buffer = &uart[0];
    
        PosicaoCursorLCD(1,0);
        EscreveFraseRamLCD("5");
    
        if(PrimeiraPassagem == 0)
        {
            LimpaDisplay();
            PrimeiraPassagem = 1;
        }

        /* Write welcome screen on LCD line 1 */
        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD(MsgPrimLinhaTask1);

        /* Write welcome screen on LCD line 2 */
        PosicaoCursorLCD(1,12);
        EscreveInteiroLCD(Code);
        EscreveFraseRamLCD("  ");   //vazio para apagar lcd apos fim da transmisão
        UART_Write(DataTx);
       
        if(36==Code)
        {
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD("inicio");
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD("      ");
        }
        
        if(42==Code)
        {
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD("Fim");
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD("      ");
        } 
        PosicaoCursorLCD(2,7);
        EscreveFraseRamLCD(Code);
        EscreveFraseRamLCD(" ");    //vazio para apagar lcd apos fim da transmisão            
    }
    LATBbits.LATB6 = ~LATBbits.LATB6;
}

/**
 *  \brief ISR
 *  
 *  \return none
 *  
 *  \details Interrupt service routine (be careful snce PIC has only one interrupt vector, based on that, the way you check the 	interrupt flag will be the priority)
 */
void interrupt isr(void)
{
    char  i;
    static unsigned char j = 0;

    if (PIE1bits.RCIE && PIR1bits.RCIF)     /*if interrupt Recepção UART*/
    {
        PIR1bits.RCIF = 0;
        Code = UART_Read();
    } //End if interrupt Recepção UART
    	
     //check if Timer0 interupt was triggered
    if (TMR0IF && T0IF)   
    {    
        T0IF = 0;           //set trigger for Timer0 interrupt (so it can be generated again)
        INTCONbits.TMR0IF = 0;   
        TMR0 = TIMER0_INIT_VALUE; //Set initial value of TMR0 register (for counting 1ms, as we need)	

        if (TimerBreathingLight)     TimerBreathingLight--;
        if (TimerBreathingLight <= 0)
        {
             LATBbits.LATB4 = ~LATBbits.LATB4;
             TimerBreathingLight = 100;
        }
        Timer0IntGeneraed = YES;
		
        //Refresh "time to execute" of each task        
        for (i=0; i<NUMBER_OF_TASKS; i++)
        {
            if (RecentTasksTimeToExecute[i] > 0)
                RecentTasksTimeToExecute[i]--;			
        }
    }   
}

 /**
 *  \brief main
 *  
 *  \return none
 *  
 *  \details Main function of the system
 */
void main(void) 
{
    InitHardware();
    
    /* Initialize tasks */ 
    InitTasks();   

    ConfiguraLCD();         //configure LCD display
 
    eeprom_init();
    Init_UART();

    LED_BUZZER = 1;
    __delay_ms(200);
    LED_BUZZER = 0;
    LimpaDisplay();
    
    unsigned char MsgPrimLinha[17] = "Painel Auto";
    unsigned char MsgSegLinha[17] =  "27/05/19 V 1.0";

    /* Write welcome screen on LCD line 1 */
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(MsgPrimLinha);

    /* Write welcome screen on LCD line 2 */
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(MsgSegLinha);
    __delay_ms(1000);

    LED_BUZZER = 1;
    __delay_ms(100);
    LED_BUZZER = 0;
    LimpaDisplay();

    unsigned char MsgWilson[17] = "Wilson";
    PosicaoCursorLCD(1,4);
    EscreveFraseRamLCD(MsgWilson);
    __delay_ms(1000);

    LimpaDisplay();
    unsigned char MsgJackson[17] =  "Jackson";
    PosicaoCursorLCD(1,4);
    EscreveFraseRamLCD(MsgJackson);
    __delay_ms(1000);

    LimpaDisplay();
    unsigned char MsgJuliano[17] =  "Juliano";
    PosicaoCursorLCD(1,4);
    EscreveFraseRamLCD(MsgJuliano);
    __delay_ms(1000);

    LimpaDisplay();
    LED_BUZZER = 1;
    __delay_ms(100);
    LED_BUZZER = 0;
    
    //main loop 
    while(1)                      
    {
        //Verification: check if there´s a task to be executed
        if ((Timer0IntGeneraed == YES)  && (NUMBER_OF_TASKS)) 
        {
            Timer0IntGeneraed = NO;  
            ExecuteTask();	    
        }
    }
}