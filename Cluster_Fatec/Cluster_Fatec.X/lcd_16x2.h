/* IDE: MPLAB X v3.65 Compiler XC8(Free Mode) V1.45
 * File:   lcd_16x2.h
 * Author: Wilson
 *
 * 
 */

#ifndef __LCD16X2_H
#define	__LCD16X2_H

#include <stdlib.h>
#include "map_lcd_16x2.h"

/*LCD pins*/
#define RS_LCD   LATDbits.LATD1
#define E_LCD     LATDbits.LATD0
#define RW_LCD  LATDbits.LATD2
/*RD3 = LATD3*/
#define D7_LCD  LATDbits.LATD7
#define D6_LCD  LATDbits.LATD6
#define D5_LCD  LATDbits.LATD5
#define D4_LCD  LATDbits.LATD4

#define LCD_trisd   TRISD
/*LCD pins*/

/*Screns initialization*/
#define screen_1_refresh 0
void screen_1(void);
/* Screns initialization*/

/*Send data*/
void send_data_float(float data);

void send_data_8bit(unsigned char data);

void send_data_char(unsigned char data);

void send_data_int(unsigned int data);
/*Send data*/

/*LCD Initialization*/
void CONFIG_lcd16x2(void);

void send_instruction_8bit(unsigned char data);
void send_instruction_4bit(unsigned char data);

void send_str(unsigned char *data);

void start_instruction(void);

void start_data_8_bit(void);

void E_write(void);
/*LCD Initialization*/

#endif