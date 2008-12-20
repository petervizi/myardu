/**
 * @file
 * @brief Log the temperature on the computer.
 *
 * This application log sends the temperature and humidity
 * readings to the computer via serial port.
 */

#include <avr/sleep.h>
#include <avr/wdt.h>

#include <SHTxx.h>
#include <LiquidCrystal.h>

using namespace myardu;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/**
 * The sensor object.
 */
SHTxx sht(4, 13);

/**
 * The LCD object.
 */
LiquidCrystal lcd(10, 11, 12, 6, 7, 8, 9);

volatile boolean f_wdt=1;

/**
 * Setup watchdog.
 *
 * @param ii
 */
void setup_watchdog(int ii) {
    byte bb;
    int ww;
    if (ii > 9 ) ii=9;
    bb=ii & 7;
    if (ii > 7) bb|= (1<<5);
    bb|= (1<<WDCE);
    ww=bb;
    Serial.println(ww);

    MCUSR &= ~(1<<WDRF);
    // start timed sequence
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    // set new watchdog timeout value
    WDTCSR = bb;
    WDTCSR |= _BV(WDIE);
}


/**
 * Start the serial port.
 */
void setup() {
    Serial.begin(9600);

    // CPU Sleep Modes 
    // SM2 SM1 SM0 Sleep Mode
    // 0    0  0 Idle
    // 0    0  1 ADC Noise Reduction
    // 0    1  0 Power-down
    // 0    1  1 Power-save
    // 1    0  0 Reserved
    // 1    0  1 Reserved
    // 1    1  0 Standby(1)
    cbi(SMCR, SE);      // sleep enable, power down mode
    cbi(SMCR, SM0);     // power down mode
    sbi(SMCR, SM1);     // power down mode
    cbi(SMCR, SM2);     // power down mode

    setup_watchdog(7);
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
