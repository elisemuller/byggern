/*
 * menu.h
 *
 * Created: 27.09.2021 10:51:39
 *  Author: elisegm
 */ 

/**
 * @file
 * @brief Creates and navigates the game menu on the OLED display
 */

#ifndef MENU_H_
#define MENU_H_


#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include "OLED_driver.h"
#include "CAN_driver.h"
#include "xmem.h"
#include "movement_driver.h"

typedef enum {
	EASY,
	NORMAL,
	HARD,
	INSANE,
	SEE,
	CLEAR,
	VOLUME_UP,
	VOLUME_DOWN,
	NO_CHOICE
} menu_choice;


typedef struct node {
	menu_choice choice; 
	char* name; 
	char* returnval; 
	struct node* children[8]; //Tilgjengelige submenyer
	struct node* parent;
	void (*funcpt)(void);
	int num_children; 
} node;
	
typedef enum {
    GAME_MUSIC,
    WINNING_MUSIC,
    LOSING_MUSIC,
    LOBBY_MUSIC,
    BIRTHDAY_MUSIC
} playlist;

typedef struct buzzer_controll {
	int volume;
	// int tempo; kanskje?
	playlist list_title;
} buzzer;


void menu_printHello(void);

void menu_printGoodBye(void);

/**
* @brief Initializes the menu displayed on the OLED screen.
*/
void menu_init(void);

/**
* @brief State controller for the menu. Updates the display on the menu with regards to the joystick input. 
*/
void menu_state_controller(void);

/**
* @brief Creates a new item for the menu. 
* @param parent of the new menu item.
* @param name of the new menu item.
* @param fpt Pointer to function if a function is linked to the new menu item, else Null.
* @param choice selected in @p fpt.
* @return A node containing information about the new menu item 
*/
node* menu_new_item(node* parent, char* name, void (*fpt)(void), menu_choice choice);


/**
* @brief Prints the entire menu, depending on where we are in the menu selections.
* Prints an arrow indicating where we are looking in the menu.
*/
void menu_print(void);

/**
* @brief Updates the pointer indicating where we are in the menu managed by the joystick @p direction.
* @param direction of the joystick controller.
*/
void menu_move_pointer(dir direction);

/**
* @brief Sets the difficulty of the game. 
*/
void menu_setDifficulty(void);

void menu_seeHighscore(void);

void menu_clearHighscore(void);

/**
* @brief Starts the game and turns off the OLED display
*/
void startGame(void);


#endif /* MENU_H_ */