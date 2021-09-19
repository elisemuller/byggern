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

void OLED_print_arrow(uint8_t row, uint8_t col){
  OLED_pos(row, col); 
  OLED_write_data(0b00011000);
  OLED_write_data(0b00011000);
  OLED_write_data(0b01111110);
  OLED_write_data(0b00111100);
  OLED_write_data(0b00011000);
}
