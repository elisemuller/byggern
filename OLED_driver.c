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

#define BASE_ADDRESS 0x1000