#include <Arduino.h>

#ifndef _BOARD_PINS_H
#define _BOARD_PINS_H

// LEDs
#define STAT_LED 10 // PB2

// Power Control
#define ENABLE A2 // PC2

// Motor
#define STEP A0 // PC0
#define DIR A1  // PC1
#define ENC_A 2 // PD2
#define ENC_B 3 // PD3

// Buttons and Inputs
#define PPIN A3     // PC3
#define IPIN A4     // Also SDA, PC4
#define DPIN A5     // Also SCL, PC5
#define STOP_MODE 8 // PB0
#define START 9     // PB1

// TFT Display
#define TFT_RST 4 // PD4
#define TFT_CS 5  // PD5
#define SD_CS 6   // PD6
#define TFT_DC 7  // PD7

#endif
