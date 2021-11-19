/**
 * @file
 * @brief Blink driver
 */

#ifndef BLINK_H_
#define BLINK_H_


/** 
* @brief Initializes the LED-pins. 
**/
void led_enable(void);

/**
* @brief Makes the LEDs on the SAM blink alternatingly
**/
void blink(void);

#endif /* BLINK_H_ */
