/*
 * Def.h
 *
 * Created: 2015-03-22 17:40:36
 *  Author: komar
 */ 


#ifndef DEF_H_
#define DEF_H_
#include <avr/io.h>
// DEFINICJE BT
#define BT_UART_DELAY 0
#define FOSC 8000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR ( FOSC  + BAUD * 8UL  ) / (16UL * BAUD) -1
#define dataLen 8
#define BT_ERR			0
#define BT_OK			1

void USART_Init( unsigned int);
void USART_Transmit( unsigned char);
unsigned char USART_Receive( void );
void USART_interrupt_init(void);
void USART_SendBuffer(char *);
void USART_ReceiveBuffer(char *);

#endif /* DEF_H_ */