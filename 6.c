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

void klava_ini()
{
    DDRA = 0x00;
    DDRD = (1<<0)|(1<<1)|(1<<2);
}
unsigned char klava()
{   
    
    unsigned char a[3][4] = {{'1','4','7','*'},{'3','6','9','#'},{ '2','5','8','0'}};
    unsigned char i,j = 0;
    unsigned char buf = 0;
    
    for(i = 0;i<3;i++)
    {
        delay_us(30);
        PORTD = 0x00|(1<<i);
        if(PINA>0)
        {   
            buf = PINA;
            
            for(j =0;j<4;j++)
            {   delay_ms(30);
                if (buf==(0x00|(1<<j)))
                {
                    
                    return a[i][j];
                }
                else
                {
                   return 's';
                }
            }
        }    
        else
        {
            return 's';
        }
    }
    
    
}
unsigned char chislo()
{
    unsigned char num=0;
    unsigned char buf = 0;
    again:
    buf = klava();
    if((buf!='*')&&(buf!='#'))
    {
        num *=10;
        num += buf -'0';
        goto again;
    }
    return num;
}   
void chislo2(unsigned char *a);  //char reader())
void print_mk(unsigned char a)
{
	unsigned char b = a;
	unsigned char pow = 1;
	unsigned char buf =0;
	for(;b/(pow*10)>0;pow*=10);
	
	do
	{
		buf = a/pow;
		LCD_data('0'+buf);
		a = a -buf*pow;
		pow/=10;	
	}while(pow>0);
	
	
	//cout<<pow;
}
void main()
{
	
    unsigned char a = 0; 
	unsigned char b = 0; 
    klava_ini(); 
    LCD_init();
	
    while(1)
    {
      LCD_data(klava()); 
	} 
	
}
void chislo2(unsigned char *a) //char reader())
{
	char buf = 0;
	label:
    buf = klava();
	
    if(buf=='s')
    {
      goto label;  
    }
    
    LCD_data(buf);
    if((buf=='#')||(buf=='*'))
	{
		return;	
	}
	else
	{
		*a *=10;
		*a += (buf - '0');
		chislo2(a);
	}
	
	 	
}
