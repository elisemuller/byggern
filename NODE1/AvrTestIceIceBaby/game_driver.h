/*
 * game_driver.h
 *
 * Created: 25.10.2021 14:49:56
 *  Author: elisegm
 */ 

/**
 * @file
 * @brief Handles the interface with NODE2
 */

#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_

void game_set_start_flag(void);
void game_interrupt_enable(void);
void game_interrupt_disable(void);
void game_set_end_flag(void);

#endif /* GAME_DRIVER_H_ */