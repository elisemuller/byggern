/*
 * OLED_driver.h
 *
 * Created: 06.09.2021 15:26:02
 *  Author: elisegm
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64

#define OFFSET_OLED 0x0000

#define OFFSET_OLED_DATA 0x1200
#define OFFSET_OLED_CMD 0x1000

#define NUM_PAGES 8

typedef enum {
  LARGE,
  NORMAL, 
  SMALL,
} font;

typedef enum {
  SPICYBIT,
  BATMAN,
  LMFAO
  } graphic; 


void OLED_init(void);

void OLED_write_d(volatile char data); //volatile

void OLED_write_c(volatile char command);

void OLED_reset(void);

void OLED_home(void);

void OLED_goto_column(uint8_t col); 

void OLED_goto_page(uint8_t page);

void OLED_clear_page(uint8_t page);

void OLED_goto_pos(uint8_t row, uint8_t col);

void OLED_select_font(font format);

void OLED_write_char(uint8_t ch);

void OLED_print(char* data);

void OLED_set_brightness(uint8_t lvl);

void OLED_print_arrow(uint8_t row, uint8_t col); 

void OLED_print_image(graphic image); 



#endif /* OLED_DRIVER_H_ */
