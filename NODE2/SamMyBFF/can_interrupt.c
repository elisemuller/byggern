/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include <stdio.h>

#include "can_interrupt.h"
#include "sam.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "game_driver.h"
#include "buzzer_driver.h"

#define DEBUG_INTERRUPT 0

volatile input_j joystick;
volatile input_s slider;

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);
			//printf("Inside message box 1 \n\r");

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
			//printf("Inside message box 2 \n\r");
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}

		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%x ", message.data[i]);
		}
		if(DEBUG_INTERRUPT)printf("\n\r");
		
		message_data_collector(message);

	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
}


void message_data_collector(CAN_MESSAGE msg){
		switch(msg.id){
		case CAN_JOYSTICK_ID:{
			joystick.pos_x = (int8_t)msg.data[0];
			joystick.pos_y = msg.data[1];
			joystick.button_pressed = msg.data[2];
			joystick.direction = msg.data[3];
			game_update_mov_msg();
			
			break;
		}
		case CAN_SLIDER_ID:{
			slider.pos_r_slider = msg.data[0];
			slider.pos_l_slider = msg.data[1];
			slider.r_button_pressed = msg.data[2];
			slider.l_button_pressed = msg.data[3];
			game_update_mov_msg();
			break;
		}
		case CAN_GAME_START_ID:{
			game_set_state(PLAY);
			buzzer_stop_music();
			break;
		}
		case CAN_GAME_LEVEL_ID:{
			game_level lv = msg.data[0];
			game_set_level(lv);
			break;
		}
		case CAN_BUZZER_ID:{
			int buzzer_data = msg.data[0];
			if(buzzer_data == 1){
			buzzer_stop_music();
			}
			else if (buzzer_data == 2){
				game_set_state(BIRTHDAY);
				buzzer_stop_music();
			}
			break;
		}
	}
}


input_j can_get_joy_input(void){
	return joystick;
}


input_s can_get_slider_input(void){
	return slider;
}
