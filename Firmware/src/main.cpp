/**
 * @file main.cpp
 * @author Joe
 * @brief MegaMouse Source Code
 */

// AVR/System
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// Libs
#include "Encoder.h"
#include "algorithm.h"

// Pindefs and misc
#include <boardPins.h>

// Objects
Encoder lEnc(LENCA, LENCB);
Algorithm alg;

void setup(void)
{
    // Configure serial
    Serial.begin(115200);
    Serial.println(REV);

    // Ready up fresh algorithm!
    alg.init();

    // Pins
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LMOT1, OUTPUT);
    pinMode(LMOT2, OUTPUT);
}

long oldPosition = -999;

void loop()
{
    long newPosition = lEnc.read();
    if (newPosition != oldPosition)
    {
        oldPosition = newPosition;
        Serial.println(newPosition);
    }

    analogWrite(LMOT1, 120);
    analogWrite(LMOT2, 0);
}
