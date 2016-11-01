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

#include <frame.h>
#include <uart.h>
#include <acc.h>
#include <mag.h>
#include <timer.h>
#include <blink.h>
#include <string.h>
#include <util/delay.h>

typedef enum
{
	STOP,
	RUN
} app_state;

void send_frame();
void timer_interrupt(void);

app_state state = STOP;
Frame frame;

uint8_t averaged_frames = 2;

int main(void)
{
	_delay_ms(500);

	volatile uint16_t tmp;
	int8_t acc_x;
	int8_t acc_y;
	int8_t acc_z;
	float averaged_palm_x = 0;
	float averaged_palm_y = 0;
	float averaged_palm_z = 0;

	// Clear frame
	memset(&frame, 0, sizeof(Frame));

	// Initialize components
	blink_init();
	uart_init();
	acc_init();
	mag_init();
	timer_init();

	while(1)
	{
		if(state == RUN)
		{
			acc_x = acc_receive(ACC_X);
			acc_y = acc_receive(ACC_Y);
			acc_z = acc_receive(ACC_Z);

			tmp = mag_receive(MAG_X);
			frame.MagX1 = tmp;
			frame.MagX2 = (tmp >> 8);
			tmp = mag_receive(MAG_Y);
			frame.MagY1 = tmp;
			frame.MagY2 = (tmp >> 8);
			tmp = mag_receive(MAG_Z);
			frame.MagZ1 = tmp;
			frame.MagZ2 = (tmp >> 8);

			frame.FrameNr++;

			// Averaging
			averaged_palm_x -= averaged_palm_x / averaged_frames;
			averaged_palm_y -= averaged_palm_y / averaged_frames;
			averaged_palm_z -= averaged_palm_z / averaged_frames;
			averaged_palm_x += (float)acc_x / averaged_frames;
			averaged_palm_y += (float)acc_y / averaged_frames;
			averaged_palm_z += (float)acc_z / averaged_frames;

			frame.PalmX = (int8_t)averaged_palm_x;
			frame.PalmY = (int8_t)averaged_palm_y;
			frame.PalmZ = (int8_t)averaged_palm_z;

			send_frame();
		}

		_delay_ms(39);
	}

	return 0;
}

inline void send_frame()
{
	uart_put_bytes((uint8_t*)&frame, sizeof(Frame));
}

void timer_interrupt(void)
{
	uint8_t c = uart_getc();
	if(c != EMPTY_BUFFER)
	{
		switch(c)
		{
		case 'R':
			state = RUN;
			break;
		case 'S':
			state = STOP;
			break;

		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
			// averaged_frames = 2^x
			c -= '0';
			averaged_frames = (1 << c);
			break;

		case 'a':
			timer_set_frequency(100);
			break;
		case 'b':
			timer_set_frequency(50);
			break;
		case 'c':
			timer_set_frequency(25);
			break;
		case 'd':
			timer_set_frequency(20);
			break;
		case 'e':
			timer_set_frequency(10);
			break;

		default:
			break;
		}
	}
}
