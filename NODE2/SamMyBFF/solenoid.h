/**
 * @file
 * @brief Driver for controlling the solenoid
 */


#ifndef SOLENOID_H_
#define SOLENOID_H_

/**
 * @brief Configures the solenoid output pin, and sets the signal low.
 */
void solenoid_init(void);

/**
 * @brief Sets the solenoid output pin for 100 ms when the @c not_triggered flag is cleared and the button is pushed. While the button is pushed, the and the @c not_triggered is set.
 * @param button_pushed sets solenoid pin if set, else clears @c not_triggered flag.
 */
void solenoid_shoot(int button_pushed);


#endif /* SOLENOID_H_ */