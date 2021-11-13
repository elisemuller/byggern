/*
 * PID.h
 *
 * Created: 08.11.2021 14:29:31
 *  Author: emiliamo
 */ 

#include <stdint.h>


#ifndef PID_H_
#define PID_H_

void PID_controller(void);

void PID_timer_test(void);

void PID_init(void);

void PID_set_ref(void);



#endif /* PID_H_ */