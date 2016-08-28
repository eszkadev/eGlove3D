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

#if _MAGNETOMETER == HMC5883L

#include <mag.h>
#include <twi.h>
#include <util/delay.h>

#define HMCW 0x3C
#define HMCR 0x3D

#define HMC_X 0x03
#define HMC_Y 0x07
#define HMC_Z 0x05

#define MAGIC_NUMBER 2048


void hmc_transmit(uint8_t address, uint8_t value)
{
	twi_start();
	twi_write(HMCW);
	twi_write(address);
	twi_write(value);
	twi_stop();
}

uint16_t hmc_receive(uint8_t address)
{
	twi_start();
	twi_write(HMCW);
	twi_write(address);
	twi_start();
	twi_write(HMCR);

	uint16_t ret = twi_read(ACK);
	ret = (ret << 8);
	ret |= twi_read(NOACK);
	twi_stop();

	return ret;
}

void mag_init(void)
{
	hmc_transmit(0x00, 0x70);
	hmc_transmit(0x01, 0xA0);
	hmc_transmit(0x02, 0x00);

	_delay_ms(7);
}

uint16_t mag_receive(mag_axis axis)
{
	uint8_t address;

	switch(axis)
	{
	case MAG_X:
		address = HMC_X;
		break;
	case MAG_Y:
		address = HMC_Y;
		break;
	case MAG_Z:
		address = HMC_Z;
		break;
	}

	return (hmc_receive(address) + MAGIC_NUMBER);
}

#endif
