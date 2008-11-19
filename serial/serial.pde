// -*- mode:c++ -*-

#include <WProgram.h>

int switchPin = 2;

void setup() {
    Serial.begin(9600);
    Serial.println("hello world");
    pinMode(switchPin, INPUT);
}

void loop() {
    Serial.print("Read switch input: ");
    Serial.println(digitalRead(switchPin));
    delay(100);
}
