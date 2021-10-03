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

//typedef void (*functionPointer)(void);


typedef struct node {
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

node* menu_new_item(node* parent, char* name, void (*fpt)(void));

void menu_print(void);

void menu_move_pointer(dir direction);


#endif /* MENU_H_ */