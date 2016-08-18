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

#include <config.h>

#if _PLATFORM == ATMEGA328

#include <timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t timer_frequency = 25;

#define PRESCALE_FACTOR 1024
#define OCR0_VALUE ((_CLOCK/timer_frequency/2/PRESCALE_FACTOR)-1)

extern void timer_interrupt(void);

ISR(TIMER0_COMPA_vect)
{
	timer_interrupt();
}

void timer_init(void)
{
	OCR0A = (uint8_t)OCR0_VALUE;
	TCNT0 = 0;

	TCCR0A |= (1 << WGM01); // CTC mode
	TCCR0B |= (1 << CS00) | (1 << CS02); // prescaler clk/1024
	TIMSK0 |= (1 << OCIE0A); // Enable interrupt
}

void timer_set_frequency(uint16_t frequency)
{
	timer_frequency = frequency;

	cli();
	timer_init();
	sei();
}

#endif
