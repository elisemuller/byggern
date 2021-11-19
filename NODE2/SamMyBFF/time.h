/**
 * @file
 * @brief Driver for time handling
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

/**
 * @brief Returns the current value of @p us_counter in either us, ms or s.
 * @param count The wanted unit of the returned time.
 */
int time_get_count(time count);


#endif /* TIME_H_ */