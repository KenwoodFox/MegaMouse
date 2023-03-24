/**
 * @file main.cpp
 * @author Joe
 * @brief MegaMouse Source Code
 */

// AVR/System
#include <Arduino.h>

// Pindefs and misc
#include <boardPins.h>

void setup(void)
{
    // Configure serial
    Serial.begin(115200);
    Serial.println(REV);
}

void loop()
{
    delay(1000);
}
