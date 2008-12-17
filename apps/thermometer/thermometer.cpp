/**
 * @file
 * @brief Thermometer application.
 *
 * The Arduino samples the SHT71 and displays the temperature and
 * humidity values on the LCD.
 */
#include <SHTxx.h>
#include <LiquidCrystal.h>

/**
 * The sensor object.
 */
myardu::SHTxx sht(4, 13);

/**
 * The LCD object.
 */
LiquidCrystal lcd(10, 11, 12, 6, 7, 8, 9);

/**
 * No setup for this application.
 */
void setup() {

}

/**
 * Sample the sensor and display results on the LCD.
 */
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
