/*
 * 4.c
 *
 * Created: 13.10.2018 11:46:30
 * Author: Student
 */

#include <io.h>
#include <delay.h>
void tochka()
{
     unsigned char i;
     for(i = 0;i<157;i++)
     {
        PORTE = 0b00110000;
        PORTB = 0b00010000;
        delay_ms(1.67);
        PORTB = 0b00000000;
        delay_ms(1.67);   
     }
    PORTE = 0b00000000;
}
void palka()
{    
     unsigned char i;
     for(i = 0;i<254;i++)
     {
        PORTE = 0b00001000;
        PORTB = 0b00010000;
        delay_ms(1.67);
        PORTB = 0b00000000;
        delay_ms(1.67);   
     }
     for(i = 0;i<200;i++)
     {
        PORTE = 0b00001000;
        PORTB = 0b00010000;
        delay_ms(1.67);
        PORTB = 0b00000000;
        delay_ms(1.67);   
     }
    PORTE = 0b00000000;
}
void bukva(char *a)
{
 unsigned char i;
 for(i = 0;a[i] !='\0';i++)
 {
    if(a[i]=='1')
    {
        palka();
    }
    else
    {
       tochka();
    }
    delay_ms(500);
 }  
}
void main(void)

{   
    unsigned char i;
    char name[6][4] = {{'0','0','0','1'},{'0','1'},{'0','1','0'},{'1','0','1'},{'1','1','1'},{'0','1','1'}};
    DDRE = 0b00111000;
    DDRB = 0b00010000;
    while (1)
        {
          for(i = 0;i<6;i++)
          {
            bukva(name[i]);
            delay_ms(1000);
          }
          delay_ms(5000);        
        }
}
                                                     
