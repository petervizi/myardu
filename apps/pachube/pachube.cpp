/**
 * @file
 * @brief Log the temperature on the computer.
 *
 * This application log sends the temperature and humidity
 * readings to the computer via serial port.
 *
 * The first value is the temperature in °C, the second in is the
 * relative humidity. These are separated by space.
 */

#include <SHTxx.h>
using namespace myardu;

/**
 * The sensor object.
 */
SHTxx sht(4, 13);

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
    float temp = 0;
    float hum = 0;
    while (true) {
	temp = sht.getTemp();
	hum = sht.getHum();
	Serial.print(temp);
	Serial.print(" ");
	Serial.println(hum);
	delay(30000);
    }
}
