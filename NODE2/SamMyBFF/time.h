/*
 * time.h
 *
 * Created: 01.11.2021 16:53:28
 *  Author: elisegm
 */ 


#ifndef TIME_H_
#define TIME_H_


typedef enum {
	us,
	ms,
	s
} time;


/**
 * @brief Sets a time delay for @p delay ms
 * @param delay The time delay in milliseconds
 */
void time_delay_ms(int delay);


/**
 * @brief Sets a time delay for @p delay us
 * @param delay The time delay in microseconds
 */
void time_delay_us(int delay);


int time_get_count(time count);


#endif /* TIME_H_ */