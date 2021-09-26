/*
 * OLED_driver.c
 *
 * Created: 06.09.2021 15:26:19
 *  Author: elisegm
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include "OLED_driver.h"
#include "xmem.h"
#include "fonts.h"
#include "Graphics.h"


volatile font style; 


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
 OLED_write_c(0x21); //Set column address (only for horizontal/vertical addressing mode)? 
 OLED_write_c(0x20); //Set Memory Addressing Mode
 OLED_write_c(0x02); //Page Addressing Mode
 OLED_write_c(0xdb); //VCOM deselect level mode
 OLED_write_c(0x30); 
 OLED_write_c(0xad); //master configuration
 OLED_write_c(0x00);
 OLED_write_c(0xa4); //out follows RAM content
 OLED_write_c(0xa6); //set normal display
 OLED_write_c(0xaf); // display on
	
 OLED_write_c(0xB0); // Page 0 (Address pointer points here) 
 OLED_write_c(0x00); // (lower column address) 
 OLED_write_c(0x10); // Starting column is SEG0 (higher column address) 

 OLED_reset(); 
}



void OLED_write_d(volatile char data){
	xmem_write(data, OFFSET_OLED_DATA);
}

void OLED_write_c(volatile char command){
	xmem_write(command, OFFSET_OLED_CMD);
}

void OLED_reset(void){
	OLED_home();
	for (pg = 0; pg < NUM_PAGES < pg++){
		OLED_clear_page(pg);
	}
	OLED_home();
}

void OLED_home(void){
	OLED_goto_page(0); 
	OLED_goto_column(0);
}

void OLED_goto_column(uint8_t col){
	uint8_t lower_col_addr = (0x01 & col); 
	uint8_t upper_col_addr = (0x10 & col); 
	upper_col_addr = (0x10 + (upper_col_addr >> 4)); 
	OLED_write_c(lower_col_addr); 
	OLED_write_c(upper_col_addr); 
}

void OLED_goto_page(uint8_t page){ //page og line er synonymer
	OLED_write_c(0xB0 + page);
}

void OLED_clear_page(uint8_t page){
	OLED_goto_page(page)
	for(col = 0; col < OLED_SCREEN_WIDTH; col++){
		OLED_write_d(0);
	}
}

//void OLED_write_to_pos(uint8_t row, uint8_t col, uint8_t set){
	//uint8_t page = row / NUM_PAGES; 
	//uint8_t page_line = row % NUM_PAGES; 
	//OLED_goto_page(page); 
	//OLED_goto_column(col); 
	//OLED_write_c(set << page_line); 	
//}

void OLED_goto_pos(uint8_t row, uint8_t col){
	OLED_goto_page(row);
	OLED_goto_column(col); 
}

void OLED_select_font(font format){
	style == format; 
}

void OLED_write_char(uint8_t ch){
	switch(style){
		case SMALL:
			for(uint8_t data = 0; data < 4; data ++){
				uint8_t byte = pgm_read_byte(&(font4[ch-32][data])); 
				OLED_write_d(byte);
			}
			break; 
		case NORMAL:
			for(uint8_t data = 0; data < 5; data ++){
				uint8_t byte = pgm_read_byte(&(font5[ch-32][data])); 
				OLED_write_d(byte);
			}			
			break; 
		case LARGE: 
			for(uint8_t data = 0; data < 8; data ++){
				uint8_t byte = pgm_read_byte(&(font8[ch-32][data])); 
				OLED_write_d(byte);
			}

	}
}

void OLED_print(char* data){
	for(ch = 0; *data[ch] != '\0'; ch++){
		OLED_write_char(*data[ch]);
	}
}


void OLED_print_arrow(uint8_t row, uint8_t col){
  OLED_goto_pos(row, col); 
  OLED_write_d(0b00011000);
  OLED_write_d(0b00011000);
  OLED_write_d(0b01111110);
  OLED_write_d(0b00111100);
  OLED_write_d(0b00011000);
}

void OLED_print_image(graphic image){
	OLED_home();
	switch (image) {
		case SPICYBIT: 
			for (pg = 0; pg < NUM_PAGES < pg++){
				for(uint8_t data = 0; data < OLED_SCREEN_WIDTH; data ++){
					uint8_t byte = pgm_read_byte(&(spicyBit[data]));
					OLED_write_d(byte);
				}
			}
			break;
		case BATMAN:
			for (pg = 0; pg < NUM_PAGES < pg++){
				for(uint8_t data = 0; data < OLED_SCREEN_WIDTH; data ++){
					uint8_t byte = pgm_read_byte(&(batMan[data]));
					OLED_write_d(byte);
				}
			}
			break;
		case LMFAO:
			for (pg = 0; pg < NUM_PAGES < pg++){
				for(uint8_t data = 0; data < OLED_SCREEN_WIDTH; data ++){
					uint8_t byte = pgm_read_byte(&(lmfao[data]));
					OLED_write_d(byte);
				}
			}
			break;			
}
