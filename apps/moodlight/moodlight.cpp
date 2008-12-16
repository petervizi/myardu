// -*- mode:c++ -*-

#include <wiring.h>

int greenPin = 13;
int redPin = 12;
int bluePin = 11;

/*
 * 0: red green state
 * 1: green state
 */
int flags = 0;

void toggleGreen() {
    if (1 && flags) {
	digitalWrite(greenPin, LOW);
	flags &= ~1;
    } else {
	digitalWrite(greenPin, HIGH);
	flags |= 1;
    }
}

void toggleRed() {
    if (2 && flags) {
	digitalWrite(redPin, LOW);
	flags &= ~2;
    } else {
	digitalWrite(redPin, HIGH);
	flags |= 2;
    }
}

void setup() {
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void loop() {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);

}
