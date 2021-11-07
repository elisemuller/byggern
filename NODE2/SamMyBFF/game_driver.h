/**
 * @file
 * @brief Game logic
 */

#ifndef GAME_DRIVER_H_
#define GAME_DRIVER_H_


typedef struct hs {
	int best_highscore;
	int last_playtime; 
} highscore;



/**
 * @brief Initializes the game.
 */
void game_init(void);

/**
 * @return Updates the highscore
 */
void game_update_highscore(void);

/**
 * @brief Controls the motor and servo with the input from the joystick controller.
 */
void game_joystick_controller(void);

/**
 * @brief Updates the movement input.
 */
void game_update_mov_msg(void);

/**
 * @brief Starts the game and is responsible for the logic of the gameplay.
 */
void game_play(void);

/**
 * @brief Sets the start flag for the game 
 */
void game_set_start_flag(void);


void game_over(void);


#endif /* GAME_DRIVER_H_ */