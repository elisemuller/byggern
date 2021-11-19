/**
 * @file
 * @brief Driver for controlling and setting up the motor
 */

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <stdint.h>
#include "can_interrupt.h"

/**
 * @brief Initializes the motor for user control
 */
void motor_init(void);

/**
 * @brief Reads position data from the encoder 
 * @return The position data of the motor
 */
int16_t motor_read_encoder(void);

/**
 * @brief Sets the speed of the motor 
 * @param speed The digital value that is converted to an analog signal of [0-5]V powering the motor speed
 */
void motor_set_speed(uint32_t speed);

/**
 * @brief Turns the motor on if @p on is set, else turns it off
 * @param on turn the motor on if set, else turns it off
 */
void motor_power(int on);

/**
 * @brief Sets the direction of the motor
 * @param direction RIGHT or LEFT
 */
void motor_set_direction(dir direction);

/**
 * @brief Controls the motor with the input from the joystick 
 */
void motor_controller(void);

/**
 * @brief Resets the encoder to 0 
 */
void motor_reset_encoder(void);


#endif /* MOTOR_DRIVER_H_ */
