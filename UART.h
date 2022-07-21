/*
 * UART.h
 *
 * Created: 7/7/2022 5:05:10 PM
 *  Author: pc
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>

#define RX_BUFFER_SIZE 128

void uart_init(uint32_t baud, uint8_t highspeed);
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c, uint32_t size);
void uart_send_string(uint8_t *c);
uint16_t uart_read_count(void);
uint8_t uart_read(void);


#endif /* UART_H_ */