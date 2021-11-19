/*
 * OLED_driver.h
 *
 * Created: 06.09.2021 15:26:02
 *  Author: elisegm
 */

/**
 * @file
 * @brief Driver for the OLED display. Configures printing and drawing on the OLED screen.
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
  MEDIUM,
  SMALL,
} font;

/**
* @brief Initializes the OLED.
*/
void OLED_init(void);

/**
* @brief Writes @p data to the OLED.
* @param char data. The data to be written to the OLED.
*/
void OLED_write_d(volatile char data); //volatile

/**
* @brief Writes a @p command to the OLED.
* @param char command. The command to be written to the OLED.
*/
void OLED_write_c(volatile char command);

/**
* @brief Reset and clears the OLED-screen.
*/
void OLED_reset(void);

/**
* @brief Sets the position on the OLED to the top left corner.
*/
void OLED_home(void);

/**
* @brief Sets the position on the OLED to a specific @p column.
* @param uint8_t col the column.
*/
void OLED_goto_column(uint8_t col);

/**
* @brief Sets the position on the OLED to a specific @p page.
* @param uint8_t page the page.
*/
void OLED_goto_page(uint8_t page);

/**
* @brief CLears a specific @p page on the OLED.
* @param uint8_t page the page to be cleared.
*/
void OLED_clear_page(uint8_t page);

/**
* @brief Sets the position on the OLED to a spesific @p row and @p column.
* @param uint8_t-row the page.
* @param uint8_t-col the column.
*/
void OLED_goto_pos(uint8_t row, uint8_t col);

/**
* @brief Selects the font for the OLED.
* @param font format style of text.
*/
void OLED_select_font(font format);

/**
* @brief Writes a @p char to the OLED.
* @param uint8_t ch the char to be written.
*/
void OLED_write_char(uint8_t ch);

/**
* @brief Prints one or more chars on the OLED-screen.
* @param char* data pointer to one or more chars containing data to be written to the OLED-screen.
*/
void OLED_print(char* data);

/**
* @brief Prints an arrow on the OLED-screen.
* @param uint8_t row the row the arrow should start at
* @param uint8_t col the column the arrow should start at
*/
void OLED_print_arrow(uint8_t row, uint8_t col);


#endif /* OLED_DRIVER_H_ */
