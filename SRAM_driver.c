/*
 * SRAM_driver.c
 *
 * Created: 06.09.2021 15:25:35
 *  Author: elisegm
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "SRAM_driver.h"
#include "xmem.h"

#define BASE_ADDRESS 0x1800