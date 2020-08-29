/* 
 * Nome do Arquivo    : lcd_16x2.h
 * 
 * Descricao                 : Armazina definicoes para o compilador.
 * 
 * Ambiente                  : MPLAB X v3.65 Compiler XC8 V1.45(Free Mode); Processador: PIC18f4550.
 * 
 * Responsavel              : Wilson Queiroz de Oliveira.
 * 
 * Vesao/Data               : 1.0V  29/08/2020
 */

#ifndef __LCD16X2_H
#define __LCD16X2_H

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

/*map lcd 16x2
 * model = HD44780U
 */

/*initialization instructions*/
#define step_1 0x03
#define step_2 0x03
#define step_3 0x03
#define step_4 0x02

//step 5
#define lcd_16x2_2lines_4bits_5x8dots 0x28
/*Function set
 * comando(0x28); 001(DL) NFXX
 * Sets interface data length(DL),
 * number of display lines(N),
 * and character font (F).
 * DL = 1: 8 bits, DL = 0: 4 bits
 * N = 1: 2 lines, N = 0: 1 line
 * F = 1: 5 × 10 dots, F = 0: 5 × 8 dots
 */

//step 6
#define lcd_16x2_cursorincrement_onwhite 0x06
/*Entry mode set
 * comando(0x06); 0000 01(ID)S
 * Sets cursor move direction and specifies display shift.
 * These operations are performed during data write
 * and read.
 * I/D = 1: Increment, I/D = 0: Decrement
 * S = 1: Accompanies display shift
 * S = 0; No shift 
 */

//step 7
#define clear_lcd_16x2 0x01

//step 8
#define lcd_16x2_lcdON_cursorON_blinkcursorOFF 0x0E
/* Display on/off control
 * comando(0x0E); 0000 1CDB
 * Sets entire display (D) on/off,
 * cursor on/off (C),
 * and blinking of cursor position character (B).
 * */

#define lcd_16x2_lcdON_cursorON_blinkcursorON 0x0F
/* Display on/off control
 * comando(0x0E); 0000 1CDB
 * Sets entire display (D) on/off,
 * cursor on/off (C),
 * and blinking of cursor position character (B).
 * 
 * initialization instructions*/

/* line        x0xx xxxx
 * column xxxx 0000
 */
#define cursor_LxC_0x0 0x80
#define cursor_LxC_0x1 0x81
#define cursor_LxC_0x2 0x82
#define cursor_LxC_0x3 0x83
#define cursor_LxC_0x4 0x84
#define cursor_LxC_0x5 0x85
#define cursor_LxC_0x6 0x86
#define cursor_LxC_0x7 0x87
#define cursor_LxC_0x8 0x88
#define cursor_LxC_0x9 0x89
#define cursor_LxC_0x10 0x8A
#define cursor_LxC_0x11 0x8B
#define cursor_LxC_0x12 0x8C
#define cursor_LxC_0x13 0x8D
#define cursor_LxC_0x14 0x8E
#define cursor_LxC_0x15 0x8F

/* line        x1xx xxxx
 * column xxxx 1111
 */
#define cursor_LxC_1x0 0xC0
#define cursor_LxC_1x1 0xC1
#define cursor_LxC_1x2 0xC2
#define cursor_LxC_1x3 0xC3
#define cursor_LxC_1x4 0xC4
#define cursor_LxC_1x5 0xC5
#define cursor_LxC_1x6 0xC6
#define cursor_LxC_1x7 0xC7
#define cursor_LxC_1x8 0xC8
#define cursor_LxC_1x9 0xC9
#define cursor_LxC_1x10 0xCA
#define cursor_LxC_1x11 0xCB
#define cursor_LxC_1x12 0xCC
#define cursor_LxC_1x13 0xCD
#define cursor_LxC_1x14 0xCE
#define cursor_LxC_1x15 0xCF

#define screen_1_refresh 10

/*
 * Send data
 */
void send_data_float(float data);

void send_data_8bit(unsigned char data);

void send_data_char(unsigned char data);

void send_data_int(unsigned int data);

/*
 * LCD Initialization
 */
void config_lcd16x2(void);

void send_instruction_8bit(unsigned char data);

void send_instruction_4bit(unsigned char data);

void send_str(unsigned char *data);

void start_instruction(void);

void start_data_8_bit(void);

void e_write(void);

#endif