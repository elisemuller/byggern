/**
 * @file
 * @brief Buzzer driver
 */

//Må vi ha denne i egen node? Hvordan skal vi få denne til å spille musikk på samme tid som vi gjør andre ting? 

#ifndef BUZZER_DRIVER_H_
#define BUZZER_DRIVER_H_

#include "melodies.h"
#include "PWM_driver.h"

/**
 * @brief Plays a single note on the buzzer
 * @param freq The frequency of the note
 * @param duration The duration of the note
 */
void buzzer_play_note(freq, duration);

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
 * @brief Adjusts the volume on the buzzer.
 * @param vol Volume of buzzer in range of 0-10. 
 */
void buzzer_adjust_volume(int vol);


/**
 * @brief Pauses current song playing on buzzer if @p pause = 1.
 * @param pause Pauses if @p pause = 1, unpauses if @p pause = 0.
 */
void buzzer_pause_music(int pause);

/**
 * @brief Plays the selected playlist @p list_title on the buzzer.
 * @param list_title Name of playlist
 */
void buzzer_play_playlist(playlist list_title);


#endif /* BUZZER_DRIVER_H_ */