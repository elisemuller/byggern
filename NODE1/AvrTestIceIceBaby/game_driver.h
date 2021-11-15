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

typedef enum {
    INIT,
    PLAY,
    LOBBY,
    GAME_OVER
} game_state;

void game_set_state(game_state state);
game_state game_get_state(void);
void game_send_start_flag(void);
void game_interrupt_enable(void);
void game_interrupt_disable(void);


#endif /* GAME_DRIVER_H_ */