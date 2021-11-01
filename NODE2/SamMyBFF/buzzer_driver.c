#include "buzzer_driver.h"
#include "sam.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "melodies.h"
#include "PWM_driver.h"

volatile int NO_TONE = 0;
volatile int STOP_SONG = 0;
volatile int PAUSE_SONG = 0;

volatile int tempo; 
volatile float dutycycle; 
volatile int notePointer; 
volatile title currentSong; 


void buzzer_init(int vol){
    

}


void buzzer_play_note(int freq, int duration){
    PWM_frequency_modify(freq);
    PWM_dutycycle_modify(dutycycle, 0, BUZZER_CHANNEL, 0);

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
    buzzer_adjust_volume(10);
    switch (song){
        case NEVER_GIVE_UP:{
            buzzer_adjust_tempo(114); //Change to make song play slower/faster
            num_notes = (sizeof(neverGiveUp) / sizeof(neverGiveUp[0]) / 2);
            buzzer_play_tune(neverGiveUp, num_notes);
            break;
        }
        case STAR_WARS:{
            buzzer_adjust_tempo(108); //Change to make song play slower/faster
            num_notes = (sizeof(starWars) / sizeof(starWars[0]) / 2);
            buzzer_play_tune(starWars, num_notes);
            break;
        }
        case BABY_ELEPHANT_WALK:{
            buzzer_adjust_tempo(132); //Change to make song play slower/faster
            num_notes = (sizeof(babyElephantWalk) / sizeof(babyElephantWalk[0]) / 2);
            buzzer_play_tune(babyElephantWalk, num_notes);
            break;
        }
        case PINK_PANTHER:{
            buzzer_adjust_tempo(120); //Change to make song play slower/faster
            num_notes = (sizeof(pinkPanther) / sizeof(pinkPanther[0]) / 2);
            buzzer_play_tune(pinkPanther, num_notes);
            break;
        }
        case TETRIS:{
            buzzer_adjust_tempo(144); //Change to make song play slower/faster
            num_notes = (sizeof(tetris) / sizeof(tetris[0]) / 2);
            buzzer_play_tune(tetris, num_notes);
            break;
        }
        case GREEN_HILL:{
            buzzer_adjust_tempo(140); //Change to make song play slower/faster
            num_notes = (sizeof(greenHill) / sizeof(greenHill[0]) / 2);
            buzzer_play_tune(greenHill, num_notes);
            break;
        }
        case CASTLEVANIA:{
            buzzer_adjust_tempo(130); //Change to make song play slower/faster
            num_notes = (sizeof(castlevania) / sizeof(castlevania[0]) / 2);
            buzzer_play_tune(castlevania, num_notes);
            break;
        }
        case HAPPY_BIRTHDAY:{
            buzzer_adjust_tempo(140); //Change to make song play slower/faster
            num_notes = (sizeof(happyBday) / sizeof(happyBday[0]) / 2);
            buzzer_play_tune(happyBday, num_notes);
            break;
        }
        case TAKE_ON_ME:{
            buzzer_adjust_tempo(140); //Change to make song play slower/faster
            num_notes = (sizeof(takeOnMe) / sizeof(takeOnMe[0]) / 2);
            buzzer_play_tune(takeOnMe, num_notes);
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

void buzzer_pause_music(int pause){
    if(PAUSE_SONG){
        if (!pause){
            buzzer_play_music(currentSong);
        }
    }
    PAUSE_SONG = pause; //Set to 0 to unpause
}

void buzzer_play_playlist(playlist list_title){
    switch (list_title){
        case LOBBY_MUSIC:{
            buzzer_play_music(BABY_ELEPHANT_WALK);
            buzzer_play_music(PINK_PANTHER);
            break;
        }
        case GAME_MUSIC: {
            buzzer_play_music(TAKE_ON_ME);
            buzzer_play_music(TETRIS);
            buzzer_play_music(CASTLEVANIA);
            buzzer_play_music(GREEN_HILL);
            break;
        }
        case LOSING_MUSIC:{
            buzzer_play_music(NEVER_GIVE_UP);
            break;
        }
        case WINNING_MUSIC: {
            buzzer_play_music(STAR_WARS);
            break;
        }
        case BIRTHDAY_MUSIC:{
            buzzer_play_music(HAPPY_BIRTHDAY);
            break;
        }
        default:{
            printf("Invalid playlist selected \r\n");
            break;
        }
    }
}