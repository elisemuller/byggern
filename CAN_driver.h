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

#define CAN_JOYSTICK_ID 1
#define CAN_SLIDER_ID 2
#define CAN_GAME_START_ID 3
#define CAN_GAME_END_ID 4
#define CAN_BUZZER_ID 5
#define CAN_GAME_LEVEL_ID 6
#define CAN_MUSIC_CONTROL 7


#include <stdio.h>

typedef struct {
  unsigned short id; //16 bit
  uint8_t length; 
  char data[8];
} can_message;


typedef struct hs {
	int best_highscore;
	int last_playtime; 
} highscore;


/**
* @brief Initializes the CAN controller. Sets mode to NORMAL_MODE
*/
void CAN_init(void);

/**
* @brief Sends CAN message of type can_message
* @param p_msg This is a poniter to the message to be sent.
*/
void CAN_send_message(can_message* p_msg);

/**
* @brief Receives CAN message.
* @param p_msg This pointer points to the storage location of the received message.
*/
void CAN_receive_message(can_message* p_msg);

/**
* @brief Initializes CAN interrupts
*/
void CAN_interrupt_init(void);

/**
* @brief Allocates information retrieved from CAN messages
*/
void CAN_message_handler(void);


highscore CAN_get_highscore(void);


#endif /* CAN_DRIVER_H_ */
