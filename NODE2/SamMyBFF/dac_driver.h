/**
 * @file
 * @brief Driver for digital to analog conversion on NODE2
 */


#ifndef DAC_DRIVER_H_
#define DAC_DRIVER_H_

/**
* @brief Initializes dac. Enables channel 1.
**/
void dac_init(void);

/**
 * @brief Sets the data on the dac channel
 * @param game_score The game score to be written to the wifi chip
 */
void dac_wr(int game_score);


#endif /* DAC_DRIVER_H_ */