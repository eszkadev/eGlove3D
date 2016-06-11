/*
 * Copyright © 2016
 * Szymon Kłos, Robert Jankowski, Wojciech Tokarski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Szymon Kłos, Robert Jankowski and Wojciech Tokarski
 *       nor the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL SZYMON KŁOS, ROBERT JANKOWSKI, WOJCIECH TOKARSKI BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

#include <uart.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t uart_rx_buffer[UART_RX_BUF_SIZE];
volatile uint8_t uart_rx_counter;
volatile uint8_t* uart_rx_in;
volatile uint8_t* uart_rx_out;

ISR(USART_RX_vect)
{
	uint8_t tmp = UDR0;

	if(uart_rx_counter < UART_RX_BUF_SIZE)
	{
		*uart_rx_in = tmp;
		uart_rx_counter++;
		if(++uart_rx_in >= uart_rx_buffer + UART_RX_BUF_SIZE)
			uart_rx_in = uart_rx_buffer;
	}
}

void uart_init(void)
{
	// Setup IO pins
	UART_DDR |= (1 << UART_TX);
	UART_DDR &= ~(1 << UART_RX);
	UART_PORT |= (1 << UART_RX);

	UBRR0H = (UBBR & 0xF00);
	UBRR0L = (uint8_t)(UBBR & 0xFF);

	#ifdef UART_DOUBLE_SPEED
		UCSR0A |= (1 << U2X0);
	#endif

	// Enable RX and TX
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << RXEN0);

	// Set frame format 8-N-1
	UCSR0C = (0x03 << UCSZ00);

	// Disable interrupts
	cli();

	// Enable RX interrupt
	UCSR0B |= (1 << RXCIE0);

	uart_rx_in = uart_rx_out = uart_rx_buffer;
	uart_rx_counter = 0;

	// Enable interrupts
	sei();
}

void uart_putc(uint8_t c)
{
	while(!(UCSR0A & (1 << UDRE0)));

	UDR0 = c;

	UCSR0A |= (1 << TXC0);
	while(!(UCSR0A & (1 << TXC0)));
}

uint8_t uart_getc(void)
{
	if(!uart_rx_counter)
		return EMPTY_BUFFER;

	cli();
	uint8_t c = *uart_rx_out;

	uart_rx_counter--;
	if(++uart_rx_out >= uart_rx_buffer + UART_RX_BUF_SIZE)
		uart_rx_out = uart_rx_buffer;

	sei();

	return c;
}

void uart_puts(uint8_t* s)
{
	while(!(UCSR0A & (1 << UDRE0)));

	while(*s != 0)
	{
		UDR0 = *s++;
		UCSR0A |= (1 << TXC0);
		while(!(UCSR0A & (1 << TXC0)));
	}
}

void uart_put_bytes(uint8_t* tab, uint8_t size)
{
	while(!(UCSR0A & (1 << UDRE0)));

	while(size--)
	{
		UDR0 = *tab++;
		UCSR0A |= (1 << TXC0);
		while(!(UCSR0A & (1 << TXC0)));
	}
}
