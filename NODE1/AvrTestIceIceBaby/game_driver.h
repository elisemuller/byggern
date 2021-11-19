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

/**
* @brief Sets the @p state of the game state machine.
* @param game_state state The state of the game state machine.
*/
void game_set_state(game_state state);

/**
* @brief Returns the @p state of the game state machine.
* @param[out] game_state The state of the game state machine.
*/
game_state game_get_state(void);

/**
* @brief Enables timer interrupts for sending game data.
*/
void game_interrupt_enable(void);

/**
* @brief Disables timer interrupts for sending game data.
*/
void game_interrupt_disable(void);

/**
* @brief Sends joystick and slider position to node 2 via CAN when timer interrupt occurs.
*/
void game_play(void)


#endif /* GAME_DRIVER_H_ */