// -*- mode:c++; -*-

#include <WProgram.h>
#include <LCD4Bit.h>

int ledPin = 1;
LCD4Bit lcd = LCD4Bit(1);
void setup() {
    Serial.begin(9600);
    lcd.init();
    //LiquidCrystal lcd = LiquidCrystal(10, 11, 12, 6, 7, 8, 9);
    pinMode(ledPin, OUTPUT);
    //    lcd.clear();
    //lcd.print("Hello world!");
    digitalWrite(ledPin, HIGH);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}
