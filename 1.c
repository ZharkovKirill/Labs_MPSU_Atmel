/*
 * 1.c
 *
 * Created: 15.09.2018 12:56:46
 * Author: Student
 */

#include <io.h>
#include <delay.h>
unsigned char perevod ( unsigned char a)
{
  
 unsigned char mass [10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 unsigned char i=0;
 for(;i<10;i++)
 {
   if(i==a)
   {
    return mass[i];
    }
 }
};
void nules()
{
    unsigned char a = 0;
    for(;a<6;a++)
    {
     PORTC = 0X00;
     PORTA = PORTA | 1<<a;
     delay_us(1);
     PORTA = 0x00;   
    }
    
};
unsigned char chifr( unsigned char a)
{
    unsigned char i = 0;
    
    while(a != 0)
    {
        i++;
        a = a/10;
    }
    
    
    return i;
}
unsigned char Digit (unsigned int d, unsigned char m){
//[]-----------------------------------------------------[]
//| Назначение: выделение цифр из разрядов пятиразрядного |
//| десятичного положительного числа |
//| Входные параметры: |
//| d - целое десятичное положительное число |
//| m - номер разряда (от 1 до 5, слева направо) |
//| Функция возвращает значение цифры в разряде m числа d |
//[]-----------------------------------------------------[]
unsigned char i = 5, a;

while(i){ // цикл по разрядам числа

a = d%10; // выделяем очередной разряд
if(i-- == m) break; // выделен заданный разряд - уходим
d /= 10; // уменьшаем число в 10 раз
}
return(a);
}
void main(void)
{
  
 unsigned char i,j;
 unsigned char b = 3;
 

 DDRA = 0xFF;
 DDRC = 0xFF;

for(j = 0;j<20;j++)
{   delay_ms(1000);
    nules();
    for(i =0;i<6;i++)
    {
    if(i<=5-chifr(b))
    {
     goto beg; 
    }
    PORTC = perevod(Digit(b,i));
    PORTA = PORTA | 1<<i;
    delay_us(1);
    PORTA = 0x00;
    beg:
    }
    
    delay_ms(1000);
    b +=2;
} 
 
}

