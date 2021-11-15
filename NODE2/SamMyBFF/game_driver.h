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



typedef enum {
	INIT,
	PLAY,
	LOBBY,
	GAME_OVER
} game_state;

typedef enum {
	UNSET,
	EASY,
	MEDIUM,
	HARD,
	INSANE
} game_level;

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
 * @brief Ends the game and records the score. 
 */
void game_ended(void);

/**
 * @brief Sets the game state to @p state. 
 * @param game_state
 */
void game_set_state(game_state state);

/**
 * @brief Returns the current game state @p game_state. 
 */
game_state game_get_state(void);

void game_set_level(game_level lv);


#endif /* GAME_DRIVER_H_ */
