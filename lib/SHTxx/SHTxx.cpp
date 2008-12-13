#include "SHTxx.h"
#include "HardwareSerial.h"

const float myardu::SHTxx::d1TableC[5] = {-39.4, -39.6, -39.7, -39.8, -40.1};
const float myardu::SHTxx::d1TableF[5] = {-38.9, -39.3, -39.5, -39.6, -40.2};

const float myardu::SHTxx::d2TableC[2] = {0.04, 0.01};
const float myardu::SHTxx::d2TableF[2] = {0.72, 0.018};

const float myardu::SHTxx::c1Table[2] = {-4.0,     -4.0};
const float myardu::SHTxx::c2Table[2] = { 0.6480,   0.0405};
const float myardu::SHTxx::c3Table[2] = {-0.00072, -0.0000028};

const float myardu::SHTxx::t1Table[2] = {0.01,    0.01};
const float myardu::SHTxx::t2Table[2] = {0.00128, 0.00008};

myardu::SHTxx::SHTxx(uint8_t dataPin, uint8_t sckPin):
    _dataPin(dataPin), _sckPin(sckPin), _vdd(VDD3500mV), _bitres(BITRESHI), _measurementDelay(2000) {
    pinMode(dataPin, OUTPUT);
    pinMode(sckPin, OUTPUT);
    reset();
}

float myardu::SHTxx::getTemp() {
    measureTemp();
    return convertTempC(_temp);
}

float myardu::SHTxx::getTempF() {
    measureTemp();
    return convertTempF(_temp);
}

float myardu::SHTxx::getHum() {
    measureHum();
    return convertHum(_hum, getTemp());
}

void myardu::SHTxx::reset(void) {
    uint8_t i;
    digitalWrite(_dataPin, HIGH);
    digitalWrite(_sckPin, LOW);
    for (i = 0; i < 9; i++) {
	digitalWrite(_sckPin, HIGH);
	digitalWrite(_sckPin, LOW);
    }
    start();
}

void myardu::SHTxx::start(void) {
    // initial state
    digitalWrite(_dataPin, HIGH);
    digitalWrite(_sckPin, LOW);
    asm("nop");
    digitalWrite(_sckPin, HIGH);
    asm("nop");
    digitalWrite(_dataPin, LOW);
    asm("nop");
    digitalWrite(_sckPin, LOW);
    delayMicroseconds(5);
    digitalWrite(_sckPin, HIGH);
    asm("nop");
    digitalWrite(_dataPin, HIGH);
    asm("nop");
    digitalWrite(_sckPin, LOW);
}

uint8_t myardu::SHTxx::measure(uint16_t *value, uint8_t* checksum, Sensor mode) {
    uint8_t error = 0;
    uint8_t i;
    start();
    switch (mode) {
    case TEMP:
	error |= write(MEASURE_TEMP);
	break;
    case HUMI:
	error |= write(MEASURE_HUMI);
	break;
    }
    pinMode(_dataPin, INPUT);
    while(1) {
	if ((digitalRead(_dataPin) == 0) || (i == 250)) {
	    break;
	}
	i++;
	delay(10);
    }    
    pinMode(_dataPin, OUTPUT);
    if (i==250) {
	return error |= 2;
    }

    *(value) = read(true) << 8;
    *(value) |= read(true);

    *(checksum) = read(false);
    return error;
}

void myardu::SHTxx::measureTemp() {
    unsigned long now = millis();
    uint8_t chsum;
    uint16_t val;
    
    if (now - _lastTempMeasurement > _measurementDelay) { // sample the sensor
	_lastTempMeasurement = now;
	if (!measure(&val, &chsum, TEMP)) {
	    _temp = val;
	}
    }
}

void myardu::SHTxx::measureHum() {
    unsigned long now = millis();
    uint8_t chsum;
    uint16_t val;
    
    if (now - _lastTempMeasurement > _measurementDelay) { // sample the sensor
	_lastHumMeasurement = now;
	if (!measure(&val, &chsum, HUMI)) {
	    _hum = val;
	}
    }
}

uint8_t myardu::SHTxx::write(byte value) {
    uint8_t error = 0;
    shiftOut(_dataPin, _sckPin, MSBFIRST, value);

    digitalWrite(_dataPin, HIGH);
    digitalWrite(_sckPin, HIGH);
    pinMode(_dataPin, INPUT);
    error = digitalRead(_dataPin);
    pinMode(_dataPin, OUTPUT);
    digitalWrite(_sckPin, LOW);
    digitalWrite(_dataPin, HIGH);

    return error == 0 ? 0 : 1;
}

uint8_t myardu::SHTxx::read(bool ack) {
    uint8_t value = 0;
    uint8_t i;
    digitalWrite(_dataPin, HIGH);
    pinMode(_dataPin, INPUT);
    for (i=128; i>0; i/=2) {
	digitalWrite(_sckPin, HIGH);
	if (digitalRead(_dataPin)) {	    
	    value = (value | i);
	}
	digitalWrite(_sckPin, LOW);  					 
    }
    pinMode(_dataPin, OUTPUT);
    if (ack) {
	digitalWrite(_dataPin, LOW);
    }
    digitalWrite(_sckPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_sckPin, LOW);
    digitalWrite(_dataPin, HIGH);
    return value;
}

float myardu::SHTxx::convertTempC(uint16_t tempReading) {
    return d1TableC[_vdd] + ((float)tempReading) * d2TableC[_bitres];
}

float myardu::SHTxx::convertTempF(uint16_t tempReading) {
    return d1TableF[_vdd] + ((float)tempReading) * d2TableF[_bitres];
}

float myardu::SHTxx::convertHum(uint16_t humReading, float temp) {
    float lin;
    lin = c1Table[_bitres] + c2Table[_bitres]*(float)humReading+c3Table[_bitres]*pow(humReading, 2);
    lin = (temp - 25.0)*(t1Table[_bitres]+t2Table[_bitres]*(float)humReading) + lin;
    if (lin > 100) {
	return 100;
    }
    if (lin < 0.1) {
	return 0.1;
    }
    return lin;
}

bool myardu::SHTxx::checkCRC(uint16_t value, uint8_t recCrc) {
    uint8_t crc = 0;
    uint8_t tmp = 0;
    uint8_t i;
    crc = CRCTable[crc ^ value];
    crc ^= CRCTable[crc ^ (value << 8)];
    for (i = 0; i < 8; i++) {
	tmp = (tmp << 1) + (recCrc & 1);
	recCrc >>= 1;
    }
    return tmp == crc;
}
