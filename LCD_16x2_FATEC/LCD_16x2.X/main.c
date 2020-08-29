/* 
 * Nome do Arquivo    : main.c
 * 
 * Descricao                 : Arquivo pricipal para Implementacao de um Display lcd_16x2.
 * 
 * Ambiente                  : MPLAB X v3.65 Compiler XC8 V1.45(Free Mode); Processador: PIC18f4550.
 * 
 * Responsavel              : Wilson Queiroz de Oliveira.
 * 
 * Vesao/Data               : 1.0V  29/08/2020
 */

#include "config.h"

void main(void) 
{
    config_mcc();
    config_lcd16x2();
    while (1)
    {
        screen_1();
    }
    return;
}

void screen_1() 
{
    send_instruction_8bit(cursor_LxC_0x0);
    char text[] ="LCD Wilson";
    send_str(text);

    send_instruction_8bit(cursor_LxC_0x12);
    unsigned int integer = -100;// 6532
    send_data_int(integer);

    send_instruction_8bit(cursor_LxC_1x0);
    unsigned char ch = 0xAA;// 170 ASICII
    send_data_char(ch);
    
    send_instruction_8bit(cursor_LxC_1x6);
    float data = 32.555555;
    send_data_float(data);

    send_instruction_8bit(cursor_LxC_1x15);
    
}