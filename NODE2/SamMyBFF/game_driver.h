/**
 * @file
 * @brief Game logic
 */

#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_


/**
 * @brief Initializes the game
 */
void game_init(void);

void game_end(void);

/**
 * @brief Counts how long the player is able to keep the game going
 */
void game_score_counter(void);

void game_joystick_controller(void);

void game_update_input_msg(void);

//void TC0_setup(void);

#endif /* GAME_DRIVER_H_ */
