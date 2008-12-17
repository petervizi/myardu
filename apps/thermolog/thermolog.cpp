/**
 * @file
 * @brief Log the temperature on the computer.
 *
 * This application log sends the temperature and humidity
 * readings to the computer via serial port.
 */

#include <SHTxx.h>
#include <LiquidCrystal.h>

using namespace myardu;

/**
 * The sensor object.
 */
SHTxx sht(4, 13);

/**
 * The LCD object.
 */
LiquidCrystal lcd(10, 11, 12, 6, 7, 8, 9);

/**
 * Start the serial port.
 */
void setup() {
    Serial.begin(9600);
}

/**
 * Sample temperature and humidity every 30 seconds, display it on the
 * LCD and send it through serial.
 */
void loop() {
    float temp;
    float hum;
    float tempf;
    while (true) {
	temp = sht.getTemp();
	tempf = sht.getTempF();
	hum = sht.getHum();
	lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(temp);
        lcd.print(" ");
        lcd.print((char)223);
        lcd.print("C");
        lcd.print(" ");
        lcd.print(tempf);
        lcd.print(" ");
        lcd.print((char)223);
        lcd.print("F");
        lcd.setCursor(0, 1);
        lcd.print(hum);
        lcd.print(" %RH");
	Serial.print(temp);
	Serial.print(" ");
	Serial.println(hum);
	delay(30000);
    }
}
