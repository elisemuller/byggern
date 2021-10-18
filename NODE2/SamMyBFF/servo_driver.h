/*
 * servo_driver.h
 *
 * Created: 18.10.2021 12:27:14
 *  Author: elisegm
 */ 


#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

#include <stdio.h>

#define MCK_DIV_32 0b0101

#define CPRE 0

void servo_pwm_init(void);

void servo_dutycycle_modify_x(int x);

#endif /* SERVO_DRIVER_H_ */