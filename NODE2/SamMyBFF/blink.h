/*
 * blink.h
 *
 * Created: 11.10.2021 15:45:46
 *  Author: elisegm
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
