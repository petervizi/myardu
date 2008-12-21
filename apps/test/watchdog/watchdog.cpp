#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

int ledPin = 13;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Serial ok");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    Serial.println("Setup ok");
}

void loop() {
    Serial.println("Loop begin");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(1000);
    wdt_enable(WDTO_8S);
    Serial.println("Loop end");
    sleep_mode();
}
