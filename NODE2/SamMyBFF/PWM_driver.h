/**
 * @file
 * @brief PWM driver
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_



/**
 * @brief Configures the pwm signal used for the PWM. 
 */
void PWM_init(void);

/**
 * @brief Modifies the @p dutycycle of the PWM on pin 44
 */
void PWM_dutycycle_modify(void);

/**
 * @brief Modifies the @p freq of the PWM for the selected @p channel.
 * @param freq Frequency of PWM signal
 */
void PWM_frequency_modify(int freq);

#endif /* PWM_DRIVER_H_ */