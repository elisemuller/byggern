/*
 * menu.h
 *
 * Created: 27.09.2021 10:51:39
 *  Author: elisegm
 */ 


#ifndef MENU_H_
#define MENU_H_


#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include "OLED_driver.h"
#include "xmem.h"
#include "Movement_driver.h"

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
	



void printHello(void);

void printGoodBye(void);


void menu_init(void);

void menu_main(void);

node* menu_new_item(node* parent, char* name, void (*fpt)(void), menu_choice choice);



/**
* @brief Prints the entire menu, depending on where we are in the menu selections.
* Prints an arrow indicating where we are looking in the menu.
* @param void
* @return void
*/
void menu_print(void);

/**
* @brief Updates the pointer indicating where we are in the menu managed by the joystick direction.
* @param void
* @return void
*/
void menu_move_pointer(dir direction);

void setDifficulty(void);

void seeHighscore(void);

void clearHighscore(void);




#endif /* MENU_H_ */