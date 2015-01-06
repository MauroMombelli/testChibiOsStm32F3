/*
 * l3g4200d.h
 *
 *  Created on: May 28, 2014
 *      Author: mauro
 */

#ifndef DCM_H_
#define DCM_H_

#include "ch.h"
#include "hal.h"

#include "lsm303dlhc.h"

struct errori{
	void (*get_estimated_error)(union quaternion, struct vector3f*);
};

void dcm_init(void);
void dcm_step(struct vector3f);
void dcm_get_quaternion(union quaternion *);

#endif /* DCM_H_ */
