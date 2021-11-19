/**
 * @file
 * @brief Test driver for debugging of NODE1 drivers
 */


#ifndef TEST_H_
#define TEST_H_

/**
* @brief For testing the ADC.
*/
void test_ADC(void);

/**
* @brief For testing reading of joystick and slider.
*/
void test_movement(void);

/**
* @brief For testing the loopback mode on CAN.
*/
void test_CAN_loopback(void);

/**
* @brief sram_test from blackboard.
*/
void test_SRAM(void);



#endif /* TEST_H_ */