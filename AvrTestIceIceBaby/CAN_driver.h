/*
 * CAN_driver.h
 *
 * Created: 06.09.2021 15:25:20
 *  Author: elisegm
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

typedef struct {
  unsigned short id; 
  unsigned char length; 
  union {
    char data[8];
    long positions[2];
  };
} can_message

#endif /* CAN_DRIVER_H_ */
