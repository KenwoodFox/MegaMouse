/**
 * @file main.cpp
 * @author Joe
 * @brief MegaMouse Source Code
 */

// AVR/System
#include <Arduino.h>
#include <Encoder.h>

// Pindefs and misc
#include <boardPins.h>

// Objects
Encoder lEnc(LENCA, LENCB);

void setup(void)
{
    // Configure serial
    Serial.begin(115200);
    Serial.println(REV);

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

    digitalWrite(LMOT1, HIGH);
    digitalWrite(LMOT2, LOW);
}
