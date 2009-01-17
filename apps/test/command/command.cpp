#include <LiquidCrystal.h>
#include <AFSoftSerial.h>
int ledp = 13; // 0 0010

// rx = 3 tx = 2
AFSoftSerial smirf = AFSoftSerial(3, 2);

void setup() {
 		pinMode(ledp, OUTPUT);
		Serial.begin(9600);
		smirf.begin(9600);
}

void loop() {
		if (smirf.available())
				Serial.print((char)smirf.read());
		if (Serial.available())
				smirf.print((char)Serial.read());
}

