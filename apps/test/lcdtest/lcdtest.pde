// -*- mode:c++; -*-

#include <LiquidCrystal.h>

// rs, rw, enable, d4, d5, d6, d7
//LiquidCrystal lcd(10, 11, 12, 2, 3, 4, 5,6, 7, 8, 9);
LiquidCrystal lcd(10, 11, 12, 6, 7, 8, 9);
void setup() { 
    pinMode(13, OUTPUT); 
}

void loop() {
    lcd.print("hello, world!");
    
    lcd.setCursor(0, 1);
    lcd.print("!dlrow ,olleh");
    while(true) {
	digitalWrite(13, HIGH);  //light the debug LED
	delay(1000);
	digitalWrite(13, LOW);  //light the debug LED
	delay(1000);
	lcd.clear();
	lcd.print("ok");
    }
}
