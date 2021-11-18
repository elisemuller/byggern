/*
 * can_controller.h
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 
/**
 * @file
 * @brief CAN controller on NODE2
 */


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include <stdint.h>

typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	char data[8];
} CAN_MESSAGE;

/**
 * @brief Initialize can bus with predefined number of rx and tx mailboxes, 
 * CAN0->CAN_MB[0] is used for transmitting
 * CAN0->CAN_MB[1,2] is used for receiving
 *			
 * @param can_br Value to be set in CAN0->CAN_BR register to match can bus bit timing
 *
 * @retval Success(0) or failure(1)
 */
uint8_t can_init_def_tx_rx_mb(void);

/**
 * @brief Initialize can bus
 *
 * @param can_br Value to be set in CAN0->CAN_BR register to match can bus bit timing
 *
 * @param num_tx_mb Number of transmit mailboxes, 	tx mb indexes: [0		, num_tx_mb-1]
 *
 * @param num_rx_mb Number of receive mailboxes, 	rx mb indexes: [num_tx_mb, num_rx_mb-1]
 *
 * @retval Success(0) or failure(1)
 */
uint8_t can_init(uint8_t num_tx_mb, uint8_t num_rx_mb);

/**
 * @brief Send can message from mailbox
 *
 * @param can_msg message to be sent
 *
 * @param tx_mb_id ID of transmit mailbox to be used
 *
 * @retval Success(0) or failure(1)
 */
uint8_t can_send(CAN_MESSAGE* can_msg, uint8_t mailbox_id);

/**
 * @brief Read can message from mailbox
 *
 * @param can_msg struct instance to save received data
 *
 * @param rx_mb_id ID of receive mailbox to be used
 *
 * @retval Success(0) or failure(1)
 */
uint8_t can_receive(CAN_MESSAGE* can_msg, uint8_t mailbox_id);


#endif /* CAN_CONTROLLER_H_ */