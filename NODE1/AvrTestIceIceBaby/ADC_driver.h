/**
 * @file
 * @brief Driver for analog to digital conversion on NODE1
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#define JOYSTICK_CHANNEL_X 1
#define JOYSTICK_CHANNEL_Y 2
#define SLIDER_CHANNEL_R 3
#define SLIDER_CHANNEL_L 4

#define NUM_JOYSTICK_CHANNELS 4



/**
 * @brief Initializes PWM signal to be used in ADC conversion
 */
void adc_init(void);

/**
 * @brief Reads and converts the data on the selected @p channel
 * @param channel The channel selected for adc conversion
 * @return The converted data
 */
volatile uint8_t adc_rd(uint8_t channel);


#endif /* ADC_DRIVER_H_ */
