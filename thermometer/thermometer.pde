// -*- mode:c++ -*-

#include <SHTxx.h>
#include <LiquidCrystal.h>


myardu::SHTxx sht(4, 13);
LiquidCrystal lcd(10, 11, 12, 6, 7, 8, 9);

void setup() {

}

void loop() {
    float temp;
    float hum;
    while (1) {
	temp = sht.getTemp();
	hum =  sht.getHum();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(temp);
	lcd.print(" ");
	lcd.print((char)223);
	lcd.print("C");
	lcd.setCursor(0, 1);
	lcd.print(hum);
	lcd.print(" %RH");
	delay(10000);
    }
}
