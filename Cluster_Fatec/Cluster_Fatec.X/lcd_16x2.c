/* IDE: MPLAB X v3.65 Compiler XC8(Free Mode) V1.45
 * File:   lcd_16x2.c
 * Author: Wilson
 *
 *
 */

#include "Config.h"
#include "lcd_16x2.h"
#include <stdio.h>
#include <stdlib.h>

void screen_1() {
    /*
     * LCD min 125khz max 250khz  
     * TIMER0 cycle = 5ms  -> TMR0 = preset_TMR0; -> mcc.h
     * screen_n() took 100ms to execute
     * screen_n_refresh  -> lcd_16x2.h
     * delay until refresh = screen_n_refresh * TIMER0 cycle
     */
    char cont_screen;
    cont_screen++;

    if (cont_screen > screen_1_refresh) 
    {
        cont_screen = 0;
        
        send_instruction_8bit(clear_lcd_16x2);
        
        send_instruction_8bit(cursor_LxC_1x0);
        //send_str(uart_test_char);
        send_data_char(uart_test_char);
        
        send_instruction_8bit(cursor_LxC_0x0);
        unsigned char velocidade = 125;
        send_data_char(velocidade);


        send_instruction_8bit(cursor_LxC_0x3);
        char text0[] ="km/h";
        send_str(text0);
        
        send_instruction_8bit(cursor_LxC_0x8);
        unsigned int RPM = 1500;
        send_data_int(RPM);
        
        send_instruction_8bit(cursor_LxC_0x13);
        char text1[] ="RPM";
        send_str(text1);
        
        send_instruction_8bit(cursor_LxC_1x3);
        unsigned int Km = 58123;
        send_data_int(Km);
        
        send_instruction_8bit(cursor_LxC_1x9);
        char text2[] =" km ";
        send_str(text2);
        
    }
}

void send_data_float(float data) 
{
    char *buf;
    int status;
    buf = ftoa(data, &status);
    send_str(buf);
}

void send_data_char(unsigned char data) 
{
    char buf[10];
    itoa(buf, data, 10);
    send_str(buf);
}

void send_data_int(unsigned int data) 
{
    char buf[10];
    utoa(buf, data, 10);
    send_str(buf);
}

/*LCD srt*/
void send_str(unsigned char *data) 
{
    for (unsigned char i = 0; *data != 0; i++) 
    {
        send_data_8bit(*data);
        data++;
    }
}

/*LCD Initialization*/
void CONFIG_lcd16x2(void) 
{
    /*
     * HD44780U
     * Initialization 4-Bit Interface
     */
    LCD_trisd = 0X00;/*LCD output*/
    
    __delay_ms(40);
    //step 1 (0x03)   
    __delay_ms(15); //wait 15ms for 4.5V , wait 40ms for 2.7V 
    send_instruction_4bit(step_1);

    //step 2 (0x03)   
    __delay_ms(5);//wait
    send_instruction_4bit(step_2);

    //step 3 (0x03)
    __delay_us(100);//wait
    send_instruction_4bit(step_3);

    //step 4 (0x02)
    send_instruction_4bit(step_4);

    //step 5
    send_instruction_8bit(lcd_16x2_2lines_4bits_5x8dots);

    //step 6
    send_instruction_8bit(lcd_16x2_cursorincrement_onwhite);

    //step 7
    send_instruction_8bit(clear_lcd_16x2);

    //step 8
    send_instruction_8bit(lcd_16x2_lcdON_cursorON_blinkcursorON);

}

void send_instruction_8bit(unsigned char data) 
{
    
    start_instruction();
    //high
    D7_LCD = (unsigned) (data & 0x80) >> 7;
    D6_LCD = (unsigned) ( data & 0x40) >> 6;
    D5_LCD = (unsigned) ( data & 0x20) >> 5;
    D4_LCD = (unsigned) ( data & 0x10) >> 4;

    E_write();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();

}

void send_instruction_4bit(unsigned char data) 
{

    start_instruction();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();
}

void send_data_8bit(unsigned char data) 
{
    
    start_data_8_bit();
    //high
    D7_LCD = (unsigned) (data & 0x80) >> 7;
    D6_LCD = (unsigned) (data & 0x40) >> 6;
    D5_LCD = (unsigned) (data & 0x20) >> 5;
    D4_LCD = (unsigned) (data & 0x10) >> 4;

    E_write();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();
}

void E_write(void) 
{
    __delay_ms(1);
    E_LCD = 1;
    E_LCD = 0;
}

void start_instruction(void) {
    __delay_ms(1);
    RS_LCD = 0;
    RW_LCD = 0;
    E_LCD = 0;
}

void start_data_8_bit(void) {
    __delay_ms(1);
    RS_LCD = 1;
    RW_LCD = 0;
    E_LCD = 0;
}
