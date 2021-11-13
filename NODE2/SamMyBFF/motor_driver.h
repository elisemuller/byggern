/*
 * motor_driver.h
 *
 * Created: 25.10.2021 09:00:48
 *  Author: elisegm
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <stdint.h>
#include "can_interrupt.h"

void motor_init(void);

uint16_t motor_read_encoder(void);



/**
 * @brief Sets the speed of the motor 
 * @param speed The digital value that is converted to an analog signal of [0-5]V powering the motor speed
 */
void motor_set_speed(uint32_t speed);

void motor_power(int on);

void motor_set_direction(dir direction);

void motor_controller(void);

void motor_reset_encoder(void);

void motor_calibrate_encoder(void);


#endif /* MOTOR_DRIVER_H_ */