/*
 * 3.c
 *
 * Created: 29.09.2018 13:03:37
 * Author: Student
 */

#include <mega128a.h>
#include <delay.h>
 
void rotatate(unsigned char s, unsigned char vec )
{   unsigned char i,speed;
    DDRC = 0x0F; // младшие разряды PORTC - выход
     
    if(vec == 1)
    {
        for(i =0;i<4;i++) 
            {
            PORTC = PORTC | (3<<i); // сформировать фронт импульса
            speed = 50 - s;
            delay_ms(speed); // задать длительность импульса
            PORTC = PORTC & ~(1<<i);
            }
    }
    else
    {
       for(i =0;i<4;i++) 
            {
            PORTC = PORTC | (12>>i); // сформировать фронт импульса
            speed = 50 - s;
            delay_ms(speed); // задать длительность импульса
            PORTC = PORTC & ~(8>>i);
            }
    }
};



void main(void)
{
     
    unsigned char i,j ;
    while (1)
    {
        //nabor 
        for(i = 0;i<45;i++)
        {
          for(j = 0;j<5;j++)
          {
           rotatate(i,1); 
          }  
        }
        //zamedl
        for(i = 45;i>0;i--)
        {
          for(j = 0;j<5;j++)
          {
           rotatate(i,1); 
          }  
        }
        //obrat
        for(i = 0;i<45;i++)
        {
          for(j = 0;j<5;j++)
          {
           rotatate(i,0); 
          }  
        }
          //const
          for(j = 0;j<45;j++)
          {
           rotatate(95,0); 
          }  
        
        for(i = 45;i>0;i--)
        {
          for(j = 0;j<5;j++)
          {
           rotatate(i,0); 
          }  
        }
    
    }
}