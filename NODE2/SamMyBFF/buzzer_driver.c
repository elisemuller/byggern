#include "buzzer_driver.h"
#include "sam.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "melodies.h"
#include "PWM_driver.h"

#define NO_TONE 0
#define STOP_SONG 0
#define PAUSE_SONG 0

volatile int tempo; 
volatile float dutycycle; 
volatile int notePointer; 
volatile title currentSong; 


void buzzer_play_note(freq, duration){
    PWM_frequency_modify(freq, BUZZER_CHANNEL);
    PWM_dutycycle_modify(dutycycle, BUZZER_CHANNEL, 0);

    //_delay_ms(noteDuration); //Tonen holder seg her så lenge da vi ikke endrer den

    // Set frequency at pwm pin 45
    // Set duty cycle of pwm to select volume. --> 0.5 er maks. 
}



void buzzer_play_tune(const int* tune, int num_notes){
    int noteCounter = notePointer;
    int divider = 0; 
    int noteDuration = 0; 
    int waitDuration = 0; 
    int wholenote = ((60000 * 4) / tempo);  

    for (noteCounter; noteCounter < num_notes * 2; noteCounter = noteCounter + 2){
        divider = tune[noteCounter + 1]; //Duration of each note in ms
        if (divider > 0){
            noteDuration = (wholenote / divider); 
        }
        else if (divider < 0) {
            noteDuration = wholenote / abs(divider);
            noteDuration *= 1.5;
        }

        waitDuration = noteDuration * 0.1; 
        noteDuration *= 0.9; 

        if (STOP_SONG) {
            buzzer_play_note(NO_TONE,0);
            notePointer = 0; 
            STOP_SONG = 0; 
            return; 
        }
        else if (PAUSE_SONG){
            buzzer_play_note(NO_TONE,0);
            notePointer = noteCounter;
            return;
        }

        buzzer_play_note(tune[noteCounter], noteDuration);

        buzzer_play_note(NO_TONE, waitDuration);

    }
    
    notePointer = 0; 
}


void buzzer_play_music(title song){
    int num_notes = 0; 
    currentSong = song; 
    switch (song){
        case NEVER_GIVE_UP:{
            buzzer_adjust_tempo(114); //Change to make song play slower/faster
            num_notes = (sizeof(neverGiveUp) / sizeof(neverGiveUp[0]) / 2);
            buzzer_play_music(neverGiveUp, num_notes);
            break;
        }
        case STAR_WARS:{
            buzzer_adjust_tempo(108); //Change to make song play slower/faster
            num_notes = (sizeof(starWars) / sizeof(starWars[0]) / 2);
            buzzer_play_music(starWars, num_notes);
            break;
        }
        default:
            printf("Invalid song choice\r\n");
            break;
        }
    
}

void buzzer_adjust_tempo(int temp){
    tempo = temp;
}

void buzzer_adjust_volume(int vol){
    if ( vol >= 0 && vol < 10)
    dutycycle = (vol/20);
}

void buzzer_pause_song(int pause){
    if(PAUSE_SONG){
        if (!pause){
            buzzer_play_music(currentSong);
        }
    }
    PAUSE_SONG = pause; //Set to 0 to unpause
}