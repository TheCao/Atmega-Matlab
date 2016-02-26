/*
 * LCD___USART___MatLab.c
 *
 * Created: 2015-03-22 17:29:54
 *  Author: komar
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Def.h"
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <inttypes.h>
// do ultradzwieku
void triger(void);
static uint16_t LastCapture;
static uint16_t odl = 0;
volatile uint16_t PulseWidth; //globalna zmienna licz¹ca szerokoœc impulsu
uint16_t tablica[9];
// tyle
char buffor[8];
int main(void)
{
	
	lcd_init();
	USART_Init(MYUBRR);
	lcd_locate(0,0);
	lcd_str("Wysylanie do ");
	lcd_locate(1,0);
	lcd_str("Matlaba");
	_delay_ms(2000);
	lcd_cls();
	
	// obsluga przerwan od ICP1
	sei();         // globalne zezwolenie na przerwania

	DDRD |= (1<<PD5);  //wyjscie
	PORTD &= ~(1<<PD5); //TRIGER

	DDRD &= ~(1<<PD6);  //wejscie ECHO
	PORTD &= ~(1<<PD6);  //ICP
	
	TCCR1B |= (1<<ICES1); // Zbocze narastaj¹ce wywo³a przerwanie
	TCCR1B |= (1<<CS11);  //preskaler = 8
	TCCR1B |= (1<<ICNC1); //NOISE CANCELLER
	TIMSK |= (1<<TICIE1);  // zezwolenie na przerwanie od ICP

	
    while(1)
    {
		/*lcd_str("Odczyt wartosci... ");
		msg = USART_Receive();
		lcd_locate(1,0);
		lcd_str("Wartosc: ");
		lcd_char(msg);
		USART_Transmit(msg);
		_delay_ms(1000);
		lcd_cls();*/
		/*for(int liczba=0;liczba<255;liczba++)
		{
			lcd_locate(0,0);
			lcd_str("Wysylanie: ");
			lcd_int(liczba);
			sprintf(buffor, "%d;", liczba ); //%2.2f dla zmiennegoprzecinka
			USART_SendBuffer(buffor);
			//_delay_ms(500);
			lcd_cls();
			
			
		}
	
		*/
		for(uint16_t a =0;a<10;a++)
		{
			triger(); //wyzwolenie
			odl = PulseWidth / 58;
			tablica[a] = odl;
		}
		lcd_locate(0,1);
		lcd_str("Odleglosc [cm]:");
		lcd_locate(1,3);
		
		lcd_int(odl);
		sprintf(buffor, "%d;",odl ); //%2.2f dla zmiennegoprzecinka
		USART_SendBuffer(buffor);
		_delay_ms(100);
		lcd_cls();
    }
}
ISR(TIMER1_CAPT_vect)
{
	// static uint16_t LastCapture;

	if( !(TCCR1B & (1<<ICES1)) ) PulseWidth = ICR1 - LastCapture;
	LastCapture = ICR1;

	TCCR1B ^= (1<<ICES1); //zbocze malej¹ce wywo³a przerwanie
}

void triger(void)
{
	PORTD &= ~(1<<PD5);
	_delay_us(2);
	PORTD |= (1<<PD5); //wystawienie jedynki na TRIG
	_delay_us(10);    //wymagane 10 uS stanu wysokiego
	PORTD &= ~(1<<PD5);  //wystawienie zera na TRIG
}