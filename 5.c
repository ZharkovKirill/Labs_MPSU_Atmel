/*
 * 5.c
 *
 * Created: 13.10.2018 12:54:50
 * Author: Student
 */

#include <io.h>
#include <stdio.h>
#include <delay.h>

#define RS 7 // выбор регистра
#define E 6 // строб передачи

void LCD_cmd(unsigned char cmd) {
//[]--------------------------------------------------[]
//| Ќазначение: запись кодов в регистр команд ∆ » |
//| ¬ходные параметры: cmd - код команды |
//[]--------------------------------------------------[]
DDRC = 0xFF; // все разр€ды PORTC на выход
DDRD |= ((1<<E)|(1<<RS));// разр€ды PORTD на выход
PORTD &= ~(1<<RS); // выбор регистра команд RS=0
PORTC = cmd; // записать команду в порт PORTC
PORTD |= (1<<E); // \ сформировать на
delay_us(5); // | выводе E строб 1-0
PORTD &= ~(1<<E); // / передачи команды
delay_ms(100); // задержка дл€ завершени€ записи
}
void LCD_init(void) {
//[]--------------------------------------------------[]
//| ДNДpДxД~ДpДЙДuД~ДyДu: ДyД~ДyДИДyДpД|ДyДxДpДИДyДС ДGДKДI |
//[]--------------------------------------------------[]
DDRC = 0xFF; // ДrДГДu ДВДpДxДВДСДtДН PORTC Д~Дp ДrДНДЗДАДt
DDRD |= ((1<<E)|(1<<RS)); // ДВДpДxДВДСДtДН PORTD Д~Дp ДrДНДЗДАДt
delay_ms (100); // ДxДpДtДuДВДwД{Дp ДtД|ДС ДЕДГДДДpД~ДАДrД|ДuД~ДyДС
LCD_cmd(0x30); 
LCD_cmd(0x30); 
LCD_cmd(0x30); 
LCD_cmd(0x38); 
LCD_cmd(0b00111100); 
LCD_cmd(0x06);

LCD_cmd(0x01); 
}
void LCD_data(char cmd) {
//[]--------------------------------------------------[]
//| Ќазначение: запись кодов в регистр команд ∆ » |
//| ¬ходные параметры: cmd - код команды |
//[]--------------------------------------------------[]
DDRC = 0xFF; // все разр€ды PORTC на выход
DDRD |= ((1<<E)|(1<<RS));// разр€ды PORTD на выход
PORTD |= (1<<RS); // выбор регистра команд RS=0
PORTC = cmd; // записать команду в порт PORTC
PORTD |= (1<<E); // \ сформировать на
delay_us(5); // | выводе E строб 1-0
PORTD &= ~(1<<E); // / передачи команды
delay_ms(100); // задержка дл€ завершени€ записи
}
void LCD_write(int pos, char c)
{   
   pos+=0x40;
   pos|=(1<<7);
   LCD_cmd(pos);
   LCD_data(c); 
}
int foo(int y, int u)
{
    int k =3*y + u/2 - 5; 
    return k ;
}
int yy(int y,int u)
{
    int k = y + 3*foo(y,u);
    return k;
}
unsigned char Code(unsigned char symb) 
{
unsigned char TabCon[] =
{0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B, 0xA7,0x4D,0x48,0x4F,0xA8,0x50,0x43,0x54,0xA9,0xAA,0x58,
0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,0x61,
0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,
0xBC,0xBD,0x6F,0xBE,0x70,0x63,0xBF,0x79,0x5C,0x78,0xE5,
0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};

//[]------------------------------------------------[]
//| Ќазначение: перекодировка символов кириллицы |
//| ¬ходные параметры: symb Ц символ ASCII |
//| ‘ункци€ возвращает код отображени€ символа |
//[]------------------------------------------------[]
return (symb >= 192 ? TabCon[symb-192]: symb)   ;
}
/*
void chislo(int a)
{
    
    int copy_a = a;
    int pow = 1;
    unsigned char len,i,buf =0;
     
    while(copy_a!=0)
    {
        copy_a/=10;
        len++;
    }
    if(len>1)
        {
            pow = 10; 
        }
    
    for(i = 0;i<len;i++)
    {
     buf = a/pow;
     a = a % pow;
     pow /=10;
     delay_us(5);
     LCD_data(len + 0x30);      
    }
    
}  */
unsigned char Digit (unsigned int d, unsigned char m){
//[]-----------------------------------------------------[]
//| Ќазначение: выделение цифр из разр€дов п€тиразр€дного |
//| дес€тичного положительного числа |
//| ¬ходные параметры: |
//| d - целое дес€тичное положительное число |
//| m - номер разр€да (от 1 до 5, слева направо) |
//| ‘ункци€ возвращает значение цифры в разр€де m числа d |
//[]-----------------------------------------------------[]
unsigned char i = 5, a;
while(i){ // цикл по разр€дам числа

a = d%10; // выдел€ем очередной разр€д
if(i-- == m) break; // выделен заданный разр€д - уходим
d /= 10; // уменьшаем число в 10 раз
}
return(a);
}

void main(void)
{
char mes[]="Y()=";
char dorova[] ="–езультат:";

unsigned char i,pos,y,j,k;
int u[5]={12,-6,-24,-42,-60};
LCD_init();
for(i =0;i<10;i++)
{
    LCD_data(Code(dorova[i]));
} 
delay_ms(5);
     
    
    while (1)
    {  
       y=0; 
        for(j = 0;j<5;j++)
        {
            LCD_write(0,'Y');
            for(i = 1;i<5;i++)
            {   if(i!=2)
                {
                    LCD_data(mes[i]);
            
                }
                else
                {
                    LCD_data('0'+j);
                    LCD_data(mes[i]);
                
                }
            }
           
            y = yy(y,u[j]);
           for (k =1;k<6;k++)
           {
            LCD_data(0x30+Digit(y,k));
           }
           
           
           delay_ms(500);
        }
    }
}           