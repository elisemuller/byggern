#include <stdio.h>
#include <stdint.h>

#include "buzzer_driver.h"
#include "sam.h"
#include "melodies.h"
#include "game_driver.h"
#include "PWM_driver.h"

volatile int NO_TONE = 0;
volatile int STOP_SONG = 0;

volatile int tempo; 
volatile int notePointer; 
volatile title currentSong; 




void buzzer_play_note(int freq, int duration){
    PWM_frequency_modify(freq);
    time_delay_ms(duration); 
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
		case SUPER_MARIO:{
			buzzer_adjust_tempo(200); //Change to make song play slower/faster
			num_notes = (sizeof(superMario) / sizeof(superMario[0]) / 2);
			buzzer_play_tune(superMario, num_notes);
			break;
		}
        default:
            printf("Invalid song choice\n\r");
            break;
        }
    
}

void buzzer_adjust_tempo(int temp){
    tempo = temp;
}


void buzzer_play_playlist(playlist list_title){
    switch (list_title){
        case LOBBY_MUSIC:{
            if(game_get_state() == LOBBY){buzzer_play_music(BABY_ELEPHANT_WALK);}
            if(game_get_state() == LOBBY){buzzer_play_music(PINK_PANTHER);}
			if(game_get_state() == LOBBY){buzzer_play_music(TAKE_ON_ME);}
            break;
        }
        case LOSING_MUSIC:{
            if(game_get_state() != PLAY) buzzer_play_music(NEVER_GIVE_UP);
            break;
        }
        case WINNING_MUSIC: {
            buzzer_play_music(STAR_WARS);
            break;
        }
        case BIRTHDAY_MUSIC:{
            if(game_get_state() != PLAY) {buzzer_play_music(HAPPY_BIRTHDAY);}
            break;
        }
        default:{
            printf("Invalid playlist selected \n\r");
            break;
        }
    }
}

void buzzer_stop_music(void){
	STOP_SONG = 1;
}