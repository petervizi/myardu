#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/io.h>
 
#define wdt_enable_int(value)   \
    __asm__ __volatile__ (  \
        "in __tmp_reg__,__SREG__" "\n\t"    \
        "cli" "\n\t"    \
        "wdr" "\n\t"    \
        "sts %0,%1" "\n\t"  \
        "out __SREG__,__tmp_reg__" "\n\t"   \
        "sts %0,%2" \
        : /* no outputs */  \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" (_BV(WDCE) | _BV(WDE)), \
        "r" (_BV(WDIF) | _BV(WDIE) | \
	     (uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) |	\
            ~_BV(WDE) | (value & 0x07)) ) \
        : "r0"  \
    )

int ledPin = 13;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Serial ok");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    Serial.println("Setup ok");
    sei();
}

void loop() {
    Serial.println("Loop begin");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(1000);
    wdt_enable_int(WDTO_8S);
    if (bit_is_set(WDTCSR, WDE)) {
	Serial.println("Watchdog System Reset Enabled");
    } else {
	Serial.println("Watchdog System Reset Disabled");
    }
    if (bit_is_set(WDTCSR, WDIE)) {
	Serial.println("Watchdog Interrupt Enabled");
    } else {
	Serial.println("Watchdog Interrupt Disabled");
    }
    Serial.println("Loop end");
    sleep_mode();
}

ISR(WDT_vect) {
    //    Serial.println("Watchdog interrupt");
    //wdt_reset();
    //sleep_mode();
}
