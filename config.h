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

#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * Config file - describes the device configuration
 */

/*
 * Platform - determines which MCU is used
 * Supported values:
 */

#define ATMEGA328 1
#define ATMEGA16  2

#define _PLATFORM ATMEGA328

/*
 * Clock - determines the clock frequency
 */

#define _CLOCK F_CPU

/*
 * Baud rate - determines the baud rate used to communicate with PC
 * Supported values:
 * clock 8 MHz:
 *     9600
 *     19200
 *     38400
 *     57600 !!! Error = 2.1 %
 *     76800
 */

#define _BAUD_RATE 9600

/*
 * Accelerometer - determines which model is used
 * Supported values:
 */

#define ADXL345 1
#define MPU6050 2

#define _ACCELEROMETER MPU6050

/*
 * Magnetometer - determines which sensor is used
 * Supported values:
 */

#define HMC5883L 1

#define _MAGNETOMETER HMC5883L

#endif /* CONFIG_H_ */
