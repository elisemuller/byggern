/*
 * OLED_driver.c
 *
 * Created: 06.09.2021 15:26:19
 *  Author: elisegm
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "OLED_driver.h"
#include "xmem.h"
#include "fonts.h"

#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64

#define OFFSET_OLED 0x0000

#define OFFSET_OLED_DATA 0x1200
#define OFFSET_OLED_CMD 0x1000



void OLED_init(void){
 OLED_write_c(0xae); // display off
 OLED_write_c(0xa1); //segment remap
 OLED_write_c(0xda); //common pads hardware: alternative
 OLED_write_c(0x12);
 OLED_write_c(0xc8); //common output scan direction:com63~com0
 OLED_write_c(0xa8); //multiplex ration mode:63
 OLED_write_c(0x3f);
 OLED_write_c(0xd5); //display divide ratio/osc. freq. mode
 OLED_write_c(0x80);
 OLED_write_c(0x81); //contrast control
 OLED_write_c(0x50);
 OLED_write_c(0xd9); //set pre-charge period
 OLED_write_c(0x21);
 OLED_write_c(0x20); //Set Memory Addressing Mode
 //OLED_write_c(0x00); //Page Addressing Mode
 //OLED_write_c(0x01); //Vertical Addressing Mode
 OLED_write_c(0xdb); //VCOM deselect level mode
 OLED_write_c(0x30); 
 OLED_write_c(0xad); //master configuration
 OLED_write_c(0x00);
 OLED_write_c(0xa4); //out follows RAM content
 OLED_write_c(0xa6); //set normal display
 OLED_write_c(0xaf); // display on
 
 //implement reset function
}



void OLED_write_d(volatile char data){
	xmem_write(data, OFFSET_OLED_DATA);
}

void OLED_write_c(volatile char command){
	xmem_write(command, OFFSET_OLED_CMD);
}

void OLED_print_arrow(uint8_t row, uint8_t col){
  OLED_pos(row, col); 
  OLED_write_d(0b00011000);
  OLED_write_d(0b00011000);
  OLED_write_d(0b01111110);
  OLED_write_d(0b00111100);
  OLED_write_d(0b00011000);
}
