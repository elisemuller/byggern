/*
 * solenoid.h
 *
 * Created: 08.11.2021 12:18:41
 *  Author: emiliamo
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

/**
 * @brief Configures the solenoid output pin, and sets the signal low.
 */
void solenoid_init(void);

/**
 * @brief Sets the solenoid output pin for 100 ms when the @p not_triggered flag is cleared and the button is pushed. While the button is pushed, the and the @p not_triggered is set.
 * @param button_pushed sets solenoid pin if set, else clears @p not_triggered flag.
 */
void solenoid_shoot(int button_pushed);


#endif /* SOLENOID_H_ */