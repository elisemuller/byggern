/*
 * CAN_driver.h
 *
 * Created: 06.09.2021 15:25:20
 *  Author: elisegm
 */ 

/**
 * @file
 * @brief Driver for CAN communication 
 */


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#define JOYSTICK_ID 1
#define SLIDER_ID 2

#include <stdio.h>

typedef struct {
  unsigned short id; //16 bit
  uint8_t length; 
  union {
    char data[8];
    long positions[2];
  };
} can_message;


/**
* @brief Initializes the CAN controller. Sets mode to LOOPBACK_MODE.
* @param uint8_t mode The wanted CAN mode
* @return void
*/
void CAN_init(uint8_t mode);

/**
* @brief Sends CAN message of type can_message
* @param can_message* p_msg This is a poniter to the message to be sent.
* @return void
*/
void CAN_send_message(can_message* p_msg);

/**
* @brief Receives CAN message.
* @param can_message* p_msg This pointer points to the storage location of the received message.
* @return void
*/
void CAN_receive_message(can_message* p_msg);

/**
* @brief Initializes CAN interrupts
* @param void
* @return void
*/
void CAN_interrupt_init(void);



#endif /* CAN_DRIVER_H_ */
