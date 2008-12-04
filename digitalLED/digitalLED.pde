// -*- mode:c++ -*-

#include <WProgram.h>

int switchPin = 2;
int ledPin = 12;
int val;
int btn;

int flags = 0;

void toggleLED() {
    if (1 & flags) {
	digitalWrite(ledPin, LOW);
	flags &= ~1;
    } else {
	digitalWrite(ledPin, HIGH);
	flags |= 1;
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("hello world");
    pinMode(switchPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    val = digitalRead(switchPin);
    if (val != btn) {
	if (val == 1) {
	    toggleLED();
	}
    }
    btn = val;
}
