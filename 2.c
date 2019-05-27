/*
 * 2.c
 *
 * Created: 29.09.2018 11:58:44
 * Author: Student
 */

#include <delay.h>   
#include <mega128a.h>

void main(void)
{

//unsigned char img [8] = {0b11110000,0b10010000,0b10010000,0b11110000,0b00001111,0b00001001,0b00001001,0b00001111};
unsigned char img [8] = {0b00001111,0b00001001 ,0b00001001,0b00001111,0b11110000, 0b10010000,0b10010000,0b11110000};
unsigned char i,j;
DDRC = 0xFF; // настроить порт PORTA на выход
DDRB = 0xFF; // настроить порт PORTA на выход

DDRA = 0xFF; // настроить порт PORTA на выход
DDRD = 0xF0; // разр€ды PD4ЕPD7 порта PORTD - выходы
 

    while (1)
    {
        
        
        PORTD = 0x00;
        for(j = 0;j<30;j++)
        { 
        for(i = 0;i<8;i++)
        {
            PORTD = i << 4;
            PORTA = img[i];
            delay_ms(3);
            
            
        } 
        }
        for(j = 0;j<30;j++)
        {
        
        for(i = 0;i<8;i++)
        {
            PORTD = i << 4;
            PORTA = ~img[i];
            delay_ms(3);
            
            
        } 
        }

    }
 
}