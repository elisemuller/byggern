/**
 * @file
 * @brief PWM driver
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include <stdio.h>

#define MCK_DIV_32 0b0101

#define SERVO_CHANNEL 44
#define BUZZER_CHANNEL 45

/**
 * @brief Configures the pwm signal used for the PWM. 
 */
void PWM_init(void);

/**
 * @brief Modifies the @p dutycycle of the PWM for the selected @p channel.
 * @param vol Volume selected for the buzzer
 * @param j_x The position of the joystick on the x axis. 
 * @param channel The selected channel for PWM modification
 * @param debug 
 */
void PWM_dutycycle_modify(float vol, int j_x, int channel, int debug);

/**
 * @brief Modifies the @p freq of the PWM for the selected @p channel.
 * @param freq Frequency of PWM signal
 */
void PWM_frequency_modify(int freq);

#endif /* PWM_DRIVER_H_ */