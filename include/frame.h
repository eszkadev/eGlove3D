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

#ifndef INCLUDE_FRAME_H_
#define INCLUDE_FRAME_H_

#include <inttypes.h>

typedef struct Frame
{
	uint8_t FrameNr;

	uint8_t LittleZ;
	uint8_t LittleY;
	uint8_t LittleX;

	uint8_t RingZ;
	uint8_t RingY;
	uint8_t RingX;

	uint8_t MiddleZ;
	uint8_t MiddleY;
	uint8_t MiddleX;

	uint8_t IndexZ;
	uint8_t IndexY;
	uint8_t IndexX;

	uint8_t ThumbZ;
	uint8_t ThumbY;
	uint8_t ThumbX;

	uint8_t PalmY; // -Y !!!!!
	uint8_t PalmZ;
	uint8_t PalmX;

	uint8_t Voltage1;
	uint8_t Voltage2;

	uint8_t MagX1;
	uint8_t MagX2;
	uint8_t MagY1;
	uint8_t MagY2;
	uint8_t MagZ1;
	uint8_t MagZ2;
} Frame;

#endif /* INCLUDE_FRAME_H_ */
