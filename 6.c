/*
 * 5.c
 *
 * Created: 13.10.2018 12:54:50
 * Author: Student
 */

#include <io.h>
#include <stdio.h>
#include <delay.h>

#define RS 7 // ����� ��������
#define E 6 // ����� ��������

void LCD_cmd(unsigned char cmd) {
//[]--------------------------------------------------[]
//| ����������: ������ ����� � ������� ������ ��� |
//| ������� ���������: cmd - ��� ������� |
//[]--------------------------------------------------[]
DDRC = 0xFF; // ��� ������� PORTC �� �����
DDRD |= ((1<<E)|(1<<RS));// ������� PORTD �� �����
PORTD &= ~(1<<RS); // ����� �������� ������ RS=0
PORTC = cmd; // �������� ������� � ���� PORTC
PORTD |= (1<<E); // \ ������������ ��
delay_us(5); // | ������ E ����� 1-0
PORTD &= ~(1<<E); // / �������� �������
delay_ms(100); // �������� ��� ���������� ������
}
void LCD_init(void) {
//[]--------------------------------------------------[]
//| �N�p�x�~�p���u�~�y�u: �y�~�y���y�p�|�y�x�p���y�� �G�K�I |
//[]--------------------------------------------------[]
DDRC = 0xFF; // �r���u ���p�x�����t�� PORTC �~�p �r�������t
DDRD |= ((1<<E)|(1<<RS)); // ���p�x�����t�� PORTD �~�p �r�������t
delay_ms (100); // �x�p�t�u���w�{�p �t�|�� �������p�~���r�|�u�~�y��
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
//| ����������: ������ ����� � ������� ������ ��� |
//| ������� ���������: cmd - ��� ������� |
//[]--------------------------------------------------[]
DDRC = 0xFF; // ��� ������� PORTC �� �����
DDRD |= ((1<<E)|(1<<RS));// ������� PORTD �� �����
PORTD |= (1<<RS); // ����� �������� ������ RS=0
PORTC = cmd; // �������� ������� � ���� PORTC
PORTD |= (1<<E); // \ ������������ ��
delay_us(5); // | ������ E ����� 1-0
PORTD &= ~(1<<E); // / �������� �������
delay_ms(100); // �������� ��� ���������� ������
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
//| ����������: ��������� ���� �� �������� �������������� |
//| ����������� �������������� ����� |
//| ������� ���������: |
//| d - ����� ���������� ������������� ����� |
//| m - ����� ������� (�� 1 �� 5, ����� �������) |
//| ������� ���������� �������� ����� � ������� m ����� d |
//[]-----------------------------------------------------[]
unsigned char i = 5, a;
while(i){ // ���� �� �������� �����

a = d%10; // �������� ��������� ������
if(i-- == m) break; // ������� �������� ������ - ������
d /= 10; // ��������� ����� � 10 ���
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
