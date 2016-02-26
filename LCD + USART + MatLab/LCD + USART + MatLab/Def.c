/*
 * Def.c
 *
 * Created: 2015-03-22 17:41:22
 *  Author: komar
 */ 
#include "Def.h"
#include <util/delay.h>
void USART_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);//|(1<<RXC);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(0<<USBS)|(1<<UCSZ0)|(1<<UCSZ1);
}
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}
void USART_interrupt_init(void)
{
	UCSRB |= (1<<RXCIE);
}
void USART_SendBuffer(char * buffer)
{
	int i = 0;
	while(buffer[i]!=0)
	{
		USART_Transmit(buffer[i]);
		_delay_ms(BT_UART_DELAY);
		i++;
		
	}
	
}
void USART_ReceiveBuffer(char * buffer)
{
	int i = 0;
	while(1)
	{
		buffer[i]= USART_Receive();
		if((buffer[i]=='\r') | (buffer[i]=='\n'))
		{
			buffer[i]=0;
			return;
		}
		_delay_ms(BT_UART_DELAY);
		i++;
	}
}