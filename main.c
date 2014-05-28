/*
 ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "ch.h"
#include "hal.h"

#include "lsm303dlh.h"
#include "l3g4200d.h"

int main(void) {

	halInit();
	chSysInit();

	palSetPadMode(GPIOE, GPIOE_LED3_RED, PAL_MODE_OUTPUT_PUSHPULL);

	palSetPad(GPIOE, GPIOE_LED3_RED);

	l3g4200d_init();
	lsm303dlh_init();
	palClearPad(GPIOE, GPIOE_LED3_RED);

	int16_t gyroscope[3];
	int16_t accerometer[3];
	int16_t magnetometer[3];

	while (TRUE) {
		read_gyroscope(gyroscope);//range:
		read_acceleration(accerometer);//range:
		read_magetometer(magnetometer);//range: -2048 2047, -4096 = overflow

		uint32_t distAcceSquared =  accerometer[0]*accerometer[0]+accerometer[1]*accerometer[1]+accerometer[2]*accerometer[2];
		uint32_t distMagneSquared =  magnetometer[0]*magnetometer[0]+magnetometer[1]*magnetometer[1]+magnetometer[2]*magnetometer[2];

		palSetPad(GPIOE, GPIOE_LED3_RED);
		chThdSleepMilliseconds(50);palClearPad(GPIOE, GPIOE_LED3_RED);
		chThdSleepMilliseconds(50);
	}
}

