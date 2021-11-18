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
	GAME_OVER,
	BIRTHDAY,
	VICTORY
} game_state;

typedef enum {
	UNSET,
	EASY,
	HARD
} game_level;

/**
 * @brief Initializes the game.
 */
void game_init(void);

/**
 * @brief Initializes the output pins for communication with wifi chip.
 */
void game_wifi_init(void);

/**
 * @brief Sets output pins according to the score input.
 * @param game_score The score to be sent to the wifi chip.
 */
void game_write_score_wifi(int game_score);

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

void game_start(void);


#endif /* GAME_DRIVER_H_ */
