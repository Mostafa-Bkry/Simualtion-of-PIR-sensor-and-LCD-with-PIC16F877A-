/*
 * File:   main.c
 * Author: acer
 *
 * Created on December 19, 2021, 5:41 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000 //Specify the XTAL crystall FREQ
#define PIR RD7
#define Buzzer RB2
#define Led RB3
#define RS RD0
#define RW RD1
#define EN RD2

void lcd_data(unsigned char data)
{
    PORTC=data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(500);
    EN = 0;
}

void lcd_command(unsigned char cmd)
{
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(500);
    EN = 0;
}

void lcd_string(const unsigned char *str, unsigned char num)
{
    unsigned char i;
    for(i = 0; i < num; i++)
    {
        lcd_data(str[i]);
    }
}

void lcd_init()
{
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

void main() //The main function
{
    TRISB2=0; //Instruct the MCU that the PORTB pins are used as Output.
    TRISB3=0;
    TRISD7=1; //Instruct the MCU that the PORTD7 pins are used as Iutput.
    PORTB=0X00;
    
    TRISC=0X00; //Instruct the MCU that the PORTC pins are used as Output.
    TRISD0=0;
    TRISD1=0;
    TRISD2=0;
    lcd_init();

    while(1) //Get into the Infinie While loop
    {
        if(PIR ==1){
            Buzzer=1;
            Led=1;
            lcd_command(0x83);
            lcd_string("MOVEMENT", 8);
            lcd_command(0xC3);
            lcd_string("IS DETECTED", 11);
            __delay_ms(50);   //Wait
            Buzzer=0;
            Led=0;
            lcd_command(0x01);
            //lcd_string("        ", 8);
            //lcd_command(0xC3);
            //lcd_string("           ", 11);
        }
    }
    return;
}
