// -*- mode:c++; -*-

#include <SHTxx.h>

using namespace myardu;

SHTxx sht(4, 13);

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

void loop() {
    while(1) {
	Serial.print(sht.getTemp());
	Serial.print(223);
	Serial.print(" °C ");
	Serial.print(sht.getHum());
	Serial.println(" %RH");
	delay(2000);
    }
}
