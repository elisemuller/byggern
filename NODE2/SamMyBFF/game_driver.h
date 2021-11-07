/**
 * @file
 * @brief Game logic
 */

#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_


/**
 * @brief Initializes the game.
 */
void game_init(void);

/**
 * @return Highscore for latest game.
 */
int game_get_highscore(void);

/**
 * @brief Controls the motor and servo with the input from the joystick controller.
 */
void game_joystick_controller(void);

/**
 * @brief Updates the input received in the CAN messages from node 2.
 */
void game_update_input_msg(void);

/**
 * @brief Starts the game and is responsible for the logic of the game.
 */
void game_start(void);


#endif /* GAME_DRIVER_H_ */
