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
#include "OLED_driver.h"
#include "xmem.h"
#include "menu.h"
#include "Movement_driver.h"
#include <util/delay.h>

volatile node* menu_position;
volatile int current_child_pointer = 0; 
volatile dir joy_dir;
volatile int neutral_flag = 0;


void printHello(void){
	OLED_print("Hello World");
}

void printGoodBye(void){
	printf("Inside goodbye\r\n");
	OLED_reset();
	OLED_print("Goodbye World");
}

void menu_init(void){
	node* root = menu_new_item(NULL, "Main menu", NULL);
	menu_position = root; 
	node* parent = menu_new_item(root, "I am parent", NULL);
	node* helloworld = menu_new_item(parent, "HelloWorld", &printHello);
	node* goodbyeworld = menu_new_item(root, "GoodbyeWorld", &printGoodBye);	
}


node* menu_new_item(node* parent, char* name, void (*fpt)(void)){
	node* newItem = (node*) malloc(sizeof(node));
	//node* newItem; 
	newItem->name = name;
	newItem->parent = parent;
	newItem->num_children = 0; 
	newItem->funcpt = fpt;
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
	for(int i= 0; i <8 ; i ++) {
		if(menu_position->children[i] != NULL){
			OLED_goto_page(i);
			if(i == current_child_pointer){
				// indicator
				OLED_print(0b00000000);
				OLED_print_arrow(i, 0);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(menu_position->children[i]->name);
			}
			else{
				// blank space
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(0b00000000);
				OLED_print(menu_position->children[i]->name);
			}
		}
	}
}

void menu_move_pointer(dir direction){
	switch(direction){
		case DOWN:{
			if(current_child_pointer < menu_position->num_children){
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
				current_child_pointer = 0;
				menu_print();
			}
			break;
		}
		case RIGHT:{
			if(menu_position->children[current_child_pointer]->num_children != 0){
				printf("I am inside the child\r\n");
				menu_position = menu_position->children[current_child_pointer];
				current_child_pointer = 0; 
				menu_print();
			}
			break;
		}
		default:
			break;
	}
}

void menu_main(){
	joy_dir = mov_get_joy_dir(); 
	//menu_print();
	switch (joy_dir){
		case NEUTRAL: {
			if (mov_read_joy_button()){
				//if (menu_position->funcpt != NULL){
				OLED_reset();
				void (*funcpt)(void) = menu_position->funcpt;
				funcpt();
					//printf("inside funcpoint");
				//}
				//menu_print();
			}
			neutral_flag = 1; 
			break;
		}
		case DOWN:{
			if(neutral_flag){
				menu_move_pointer(DOWN);
				
				//move_down
				neutral_flag = 0; 
			}
			break;
		}
		case UP:{
			if(neutral_flag){
				menu_move_pointer(UP);
				//move up
				neutral_flag = 0;
			}
			break;
		}
		case LEFT:{
			if(neutral_flag){
				menu_move_pointer(LEFT);
				//move back
				neutral_flag = 0;
			}
			break;
		}
		case RIGHT:{
			if(neutral_flag){
				menu_move_pointer(RIGHT);
				//go on in
				neutral_flag = 0;
			}
			break;
		}
	}
}
