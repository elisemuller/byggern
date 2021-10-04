/*
 * CAN_driver.h
 *
 * Created: 06.09.2021 15:25:20
 *  Author: elisegm
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdio.h>

typedef struct {
  unsigned short id; 
  // unsigned char
  uint8_t length; 
  union {
    char data[8];
    long positions[2];
  };
} can_message;


void CAN_init(void);

void CAN_send_message(can_message msg);

void CAN_receive_message(can_message* p_msg);

void CAN_interrupt_init(void);



#endif /* CAN_DRIVER_H_ */
