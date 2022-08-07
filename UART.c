/*
 * UART.c
 *
 * Created: 7/7/2022 5:04:51 PM
 *  Author: pc
 */ 
#include <UART.h>
#include <avr/interrupt.h>
#define F_CPU 16000000ul
#define RX_BUFFER_SIZE 128

volatile static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rx_count = 0;
volatile static uint8_t uart_tx_busy = 1;

ISR(USART_RX_vect)
{
	volatile static uint16_t rx_write_pos = 0; 
	
	rx_buffer[rx_write_pos] = UDR0;
	rx_count++; 
	rx_write_pos++;
	if (rx_write_pos >= RX_BUFFER_SIZE)
	{
		rx_write_pos = 0;
	}
}

ISR(USART_TX_vect)
{
	uart_tx_busy = 1;
}

void uart_init(uint32_t baud, uint8_t highspeed)
{
	uint16_t speed = 16; 
	if (highspeed != 0)
	{
		speed = 8; 
		UCSR0A |= (1 << U2X0);
	}
	
	//============calculate baud rate========= 
	baud = (F_CPU/(speed*baud)) - 1;
	UBRR0H = (baud >> 8);
	UBRR0L = baud;
	/*======= transmit/interrupt transmit and receive/interrupt receive enable =======*/
	UCSR0B = (1 << RXEN0)|(1 << TXEN0)|(1 << RXCIE0)|(1 << TXCIE0);
	
}

void uart_send_byte(uint8_t c)
{
	while(uart_tx_busy == 0); 
	uart_tx_busy = 0; 
	UDR0 = c;
}

void uart_send_array(uint8_t *c, uint32_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		uart_send_byte(c[i]);
	}
}

void uart_send_string(uint8_t *c)
{
	uint16_t i = 0; 
	do{
		uart_send_byte(c[i]);
		i++;
	}while(c[i] != '\0');
	uart_send_byte(c[i]);
		
}

uint16_t uart_read_count(void)
{
	return rx_count;
}

uint8_t uart_read(void)
{
	static uint16_t rx_read_pos = 0;
	uint8_t data = 0;
	 
	data = rx_buffer[rx_read_pos];
	
	rx_read_pos++;
	
	rx_count--;
	if(rx_read_pos >= RX_BUFFER_SIZE)
	{
		rx_read_pos = 0;
	}
	
	return data;
}