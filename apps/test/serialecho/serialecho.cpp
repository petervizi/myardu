int ledp = 4;

void setup() {
		Serial.begin(115200);
		pinMode(ledp, OUTPUT);
 		digitalWrite(ledp, HIGH);
}
void loop() {
		if (Serial.available() > 0)
				Serial.print((char)Serial.read());
}
