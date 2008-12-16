// -*- mode:c++ -*-

#include <assert.h>

int led1Pin = 12;
int led2Pin = 11;
int led3Pin = 10;
int led4Pin = 9;
int led5Pin = 8;

int potPin = 1;
int dioPin = 0;

int switchPin = 2;

int potVal;
int dioVal;
int val;
int buttonState;
int lightMode = 0;
int curLed;
bool ledDir;
bool dioState;

void nextLed() {
    digitalWrite(curLed, LOW);
    if (ledDir) {
	curLed--;
    } else {
	curLed++;
    }
    if (curLed == 8) {
	ledDir = false;
    }
    if (curLed == 12) {
	ledDir = true;
    }
    Serial.print("curLed ");
    Serial.println(curLed);
    assert((curLed >= 8) && (curLed <= 12));
    digitalWrite(curLed, HIGH);    
}

void setup () {
    pinMode(3, OUTPUT);
    pinMode(switchPin, INPUT);
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);
    pinMode(led4Pin, OUTPUT);
    pinMode(led5Pin, OUTPUT);
    Serial.begin(9600);
    buttonState = digitalRead(switchPin);
    digitalWrite(3, HIGH);
    curLed = 12;
    ledDir = true;
}

void loop() {
    val = digitalRead(switchPin);
    if (val != buttonState) {
	if (val == LOW) {
	    lightMode++;
	}	
    }
    buttonState = val;

    switch (lightMode) {
    case 0:
	digitalWrite(12, LOW);
	digitalWrite(11, LOW);
	digitalWrite(10, LOW);
	digitalWrite(9, LOW);
	digitalWrite(8, LOW);
	break;
    case 1:
	potVal = analogRead(potPin);
	nextLed();
	delay(potVal);
	break;
    case 2:
	dioVal = analogRead(dioPin);
	Serial.print("dioVal: ");
	Serial.println(dioVal);
	if (dioState) {
	    digitalWrite(12, HIGH);
	    digitalWrite(11, HIGH);
	    digitalWrite(10, HIGH);
	    digitalWrite(9, HIGH);
	    digitalWrite(8, HIGH);
	    dioState = false;
	} else {
	    digitalWrite(12, LOW);
	    digitalWrite(11, LOW);
	    digitalWrite(10, LOW);
	    digitalWrite(9, LOW);
	    digitalWrite(8, LOW);
	    dioState = true;
	}
	delay(dioVal);
	break;
    default:
	lightMode = 0;
	break;
    }
}
