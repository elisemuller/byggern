/*
 * OLED_driver.h
 *
 * Created: 06.09.2021 15:26:02
 *  Author: elisegm
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#define OFFSET_OLED 0x0000

void OLED_init(void);

void OLED_reset(void);

void OLED_home(void);

void OLED_goto_line(int line);

void OLED_clear_line(int line);

void OLED_pos(int row, int column);

void OLED_write_data(volatile char data); //volatile

void OLED_print(char* data);

void OLED_set_brightness(int lvl);



#endif /* OLED_DRIVER_H_ */
