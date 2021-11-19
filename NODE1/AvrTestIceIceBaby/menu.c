/*
 * menu.c
 *
 * Created: 27.09.2021 10:51:29
 *  Author: elisegm
 */

#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "OLED_driver.h"
#include "menu.h"
#include "movement_driver.h"
#include "CAN_driver.h"
#include "game_driver.h"


volatile node* menu_position;
volatile int current_child_pointer = 0;
volatile int previous_parent = 0;
volatile int neutral_flag = 0;
volatile input_j joystick_input;
volatile int level = 0;
volatile int buzzer_data = 3;




void menu_setDifficulty(void){
	OLED_goto_pos(2,3);
	switch(menu_position->children[current_child_pointer]->choice){
		case EASY: {
			OLED_print("Easy peacy lemon squeezy");
			level = 1;
			menu_send_can_message(CAN_GAME_LEVEL_ID);
			break;
		}
		case HARD:{
			OLED_print("So you like it hardcore huh?");
			level = 2;
			menu_send_can_message(CAN_GAME_LEVEL_ID);
			break;
		}
	}
}

void menu_seeHighscore(void){
	highscore record;
	record = CAN_get_highscore();
	char hs_text[16];
	char play_text[16];
	int best_num = record.best_highscore;
	int play_time = record.last_playtime;
	sprintf(hs_text, "Highscore: %d", best_num);
	sprintf(play_text, "Playtime %d", play_time);

	OLED_goto_pos(0,0);
	OLED_print(hs_text);
	printf("Highscore: %d \n\r", best_num);
	//OLED_print(hs_text);

	OLED_goto_pos(1,0);
	OLED_print(play_text);
	printf("Your playtime: %d \n\r", play_time);
	//OLED_print(play_text);

}

void menu_clearHighscore(void){
	// Send til CAN 2 om å cleare highscore der.

}

void menu_startGame(void){
	OLED_print(" Good Luck!");
	game_set_state(PLAY);
	OLED_reset();

	// Turn off OLED
	game_interrupt_enable();
	menu_send_can_message(CAN_GAME_START_ID);
}



void menu_control_music(void){
	switch(menu_position->children[current_child_pointer]->choice){
		case STOP: {
			if (buzzer_data == 1){
				OLED_print("   PLAYING");
				buzzer_data = 3;
			}
			else if (buzzer_data == 3){
				OLED_print("   STOPPED");
				buzzer_data = 1;
			}
			menu_send_can_message(CAN_BUZZER_ID);
			break;
		}
		case BIRTHDAY:
		{
			OLED_print("HAPPY BIRTHDAY!");
			buzzer_data = 2;
			menu_send_can_message(CAN_BUZZER_ID);
			break;
		}
	}
}

void menu_send_can_message(int CAN_ID){
	can_message menu_msg;
	menu_msg.id = CAN_ID;
	switch (CAN_ID){
		case CAN_BUZZER_ID:{
			menu_msg.length = 1;
			menu_msg.data[0] = buzzer_data;
			CAN_send_message(&menu_msg);
			break;
		}
		case CAN_GAME_START_ID:{
			menu_msg.length = 1;
			menu_msg.data[0] = 1;
			CAN_send_message(&menu_msg);
			break;
		}
		case CAN_GAME_LEVEL_ID:{
			menu_msg.length = 1;
			menu_msg.data[0] = level;
			CAN_send_message(&menu_msg);
			break;
		}
		default:{
			printf("Invalid CAN message ID");
			break;
		}
	}
}

void menu_init(void){
	OLED_init();
	//Root
	node* root = menu_new_item(NULL, "Main menu", NULL, NO_CHOICE);
	menu_position = root;

	//Main menu
	node* start_game = menu_new_item(root, "Start game", &menu_startGame, NO_CHOICE);
	node* difficulty = menu_new_item(root, "Difficulty", NULL, NO_CHOICE);
	node* highscore = menu_new_item(root, "Highscore", NULL, NO_CHOICE);
	node* sound_settings = menu_new_item(root, "Sound", NULL, NO_CHOICE);
	node* happy_bday =  menu_new_item(root, "My birthday", &menu_control_music, BIRTHDAY);

	//Difficulty
	node* easy = menu_new_item(difficulty, "Easy", &menu_setDifficulty, EASY );
	node* hard = menu_new_item(difficulty, "Hard", &menu_setDifficulty, HARD );
	//node* insane = menu_new_item(difficulty, "Insane", &menu_setDifficulty, INSANE );
	//
	////Highscore
	node* see = menu_new_item(highscore, "See", &menu_seeHighscore, SEE );
	node* clear = menu_new_item(highscore, "Clear", &menu_clearHighscore, CLEAR );

	////Sound
	 node* stop = menu_new_item(sound_settings, "Stop/Play", &menu_control_music, STOP);

	menu_print();
}


node* menu_new_item(node* parent, char* name, void (*fpt)(void), menu_choice choice){
	node* newItem = (node*) malloc(sizeof(node));
	newItem->name = name;
	newItem->parent = parent;
	newItem->num_children = 0;
	newItem->funcpt = fpt;
	newItem->choice = choice;
	for(int i = 0; i < 8; i++){
		newItem->children[i] = NULL;
	}
	for(int i = 0; i < 8; i++){
		if(parent->children[i] == NULL){
			parent->children[i] = newItem;
			parent->num_children++;
			return newItem;
		}
	}
	return NULL;
}


void menu_print(void){
	OLED_reset();
	for(int pg= 0; pg <8 ; pg ++) {
		if(menu_position->children[pg] != NULL){
			OLED_goto_pos(pg, 0);
			if(pg == current_child_pointer){
				OLED_print(" ");
				OLED_print_arrow(pg, 0);
				OLED_print("  ");
				OLED_print(menu_position->children[pg]->name);
			}
			else{
				OLED_print(" ");
				OLED_print(menu_position->children[pg]->name);
			}
		}
	}
}


void menu_move_pointer(dir direction){
	switch(direction){
		case DOWN:{
			if(current_child_pointer < menu_position->num_children - 1){
				current_child_pointer++;
				menu_print();
			}
			break;
		}
		case UP:{
			if(current_child_pointer > 0){
				current_child_pointer--;
				menu_print();
			}
			break;
		}
		case LEFT:{
			if(menu_position->parent != NULL){
				menu_position = menu_position->parent;
				current_child_pointer = previous_parent;
				menu_print();
			}
			break;
		}
		case RIGHT:{
			if(menu_position->children[current_child_pointer]->num_children != 0){
				menu_position = menu_position->children[current_child_pointer];
				previous_parent = current_child_pointer;
				current_child_pointer = 0;
				menu_print();
			}
			break;
		}
		default:
			break;
	}
}


void menu_state_controller(){
	joystick_input = mov_get_joy_input();
	switch (joystick_input.direction){
		case NEUTRAL: {
			if (mov_read_button(jb)){
				if (menu_position->children[current_child_pointer]->funcpt != NULL){
					OLED_reset();
					menu_position->children[current_child_pointer]->funcpt();
				}
			}
			neutral_flag = 1;
			break;
		}
		case DOWN:{
			if(neutral_flag){
				menu_move_pointer(DOWN);
				neutral_flag = 0;
			}
			break;
		}
		case UP:{
			if(neutral_flag){
				menu_move_pointer(UP);
				neutral_flag = 0;
			}
			break;
		}
		case LEFT:{
			if(neutral_flag){
				menu_move_pointer(LEFT);
				neutral_flag = 0;
			}
			break;
		}
		case RIGHT:{
			if(neutral_flag){
				menu_move_pointer(RIGHT);
				neutral_flag = 0;
			}
			break;
		}
	}
}
