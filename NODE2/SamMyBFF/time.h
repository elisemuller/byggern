/*
 * time.h
 *
 * Created: 01.11.2021 16:53:28
 *  Author: elisegm
 */ 


#ifndef TIME_H_
#define TIME_H_


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
 * @brief Starts the time counter 
 */
void time_start_counter(void);

/**
 * @brief Increases the @p counter for every second
 * @param counter that counts the time
 */
void time_update_counter(int &counter);

/**
 * @brief Stops the time counter 
 */
void time_stop_counter(void);


#endif /* TIME_H_ */