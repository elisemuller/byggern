/**
 * @file
 * @brief Driver for playing music on the piezo buzzer
 */


#ifndef BUZZER_DRIVER_H_
#define BUZZER_DRIVER_H_

#include "melodies.h"

/**
 * @brief Plays a single note on the buzzer
 * @param freq The frequency of the note
 * @param duration The duration of the note
 */
void buzzer_play_note(int freq, int duration);

/**
 * @brief Plays the melody of the song on the buzzer
 * @param tune The melody of the song
 * @param num_notes The size of the melody
 */
void buzzer_play_tune(const int* tune, int num_notes);

/**
 * @brief Selects and plays the @p song on the buzzer.
 * @param song The title of the song.
 */
void buzzer_play_music(title song);


/**
 * @brief Adjusts the tempo of the song being played on the buzzer.
 * @param temp The frequency of the notes in the song.
 */
void buzzer_adjust_tempo(int temp);


/**
 * @brief Plays the selected playlist @p list_title on the buzzer.
 * @param list_title Name of playlist
 */
void buzzer_play_playlist(playlist list_title);

/**
 * @brief Stops music from playing on buzzer if @p stop is set
 * @param stop music when 1, else continues playing
 */
void buzzer_stop_music(int stop);


#endif /* BUZZER_DRIVER_H_ */