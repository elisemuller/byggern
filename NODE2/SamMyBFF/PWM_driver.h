/**
 * @file
 * @brief PWM driver
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_



/**
 * @brief Configures the pwm signal. 
 */
void PWM_init(void);

/**
 * @brief Modifies the dutycycle of the PWM on pin 44 used by the servo. 
 */
void PWM_dutycycle_modify(void);

/**
 * @brief Modifies the @p freq of the PWM on pin 45 used by the piezo buzzer 
 * @param freq Frequency of PWM signal
 */
void PWM_frequency_modify(int freq);

#endif /* PWM_DRIVER_H_ */