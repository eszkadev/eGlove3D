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

#include <adxl345.h>
#include <twi.h>

void adxl_init(void)
{
	twi_init();
	// Continuous measurement
	adxl_transmit(0x2D, 0x08);
	// Resolution
	adxl_transmit(0x31, 0x00); // Full - 0x08
	// Frequency of measurement (0x0A - 100Hz, 0x09 - 50Hz)
	adxl_transmit(0x2C, 0x09);
}

void adxl_transmit(uint8_t reg, uint8_t value)
{
	twi_start();
	twi_write(ADXLW);
	twi_write(reg);
	twi_write(value);
	twi_stop();
}

uint16_t adxl_receive(uint8_t reg)
{
	uint16_t ret = 0;
	uint16_t tmp;
	switch (reg)
	{
	case ADXL_X:
		twi_start();
		twi_write(ADXLW);
		twi_write(0x32);
		twi_start();
		twi_write(ADXLR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(ADXLW);
		twi_write(0x33);
		twi_start();
		twi_write(ADXLR);
		ret = (twi_read(NOACK) << 8) | tmp;
		twi_stop();
	break;
	case ADXL_Y:
		twi_start();
		twi_write(ADXLW);
		twi_write(0x34);
		twi_start();
		twi_write(ADXLR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(ADXLW);
		twi_write(0x35);
		twi_start();
		twi_write(ADXLR);
		ret = (twi_read(NOACK) << 8) | tmp;
		twi_stop();
	break;
	case ADXL_Z:
		twi_start();
		twi_write(ADXLW);
		twi_write(0x36);
		twi_start();
		twi_write(ADXLR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(ADXLW);
		twi_write(0x37);
		twi_start();
		twi_write(ADXLR);
		ret = (twi_read(NOACK) << 8) | tmp;
		twi_stop();
	break;
	}
	return ret;
}
