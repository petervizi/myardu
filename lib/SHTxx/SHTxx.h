#ifndef SHTXX_H_
#define SHTXX_H_

/**
 * @file SHTxx.h Sensor class.
 * 
 * @author peter.vizi@gmail.com
 */

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <wiring.h>
#ifdef SHT_DEBUG
#include <HardwareSerial.h>
#endif

namespace myardu {
    
	
    /**
     * Table for calculating CRC of the received data.
     */
    static const uint8_t CRCTable[256] = {0, 49, 98, 83, 196, 245, 166, 151, 185, 136, 219, 234, 125, 76, 31, 46, 67, 114, 33, 16, 135, 182, 229, 212, 250, 203, 152, 169, 62, 15, 92, 109, 134, 183, 228, 213, 66, 115, 32, 17, 63, 14, 93, 108, 251, 202, 153, 168, 197, 244, 167, 150, 1, 48, 99, 82, 124, 77, 30, 47, 184, 137, 218, 235, 61, 12, 95, 110, 249, 200, 155, 170, 132, 181, 230, 215, 64, 113, 34, 19, 126, 79, 28, 45, 186, 139, 216, 233, 199, 246, 165, 148, 3, 50, 97, 80, 187, 138, 217, 232, 127, 78, 29, 44, 2, 51, 96, 81, 198, 247, 164, 149, 248, 201, 154, 171, 60, 13, 94, 111, 65, 112, 35, 18, 133, 180, 231, 214, 122, 75, 24, 41, 190, 143, 220, 237, 195, 242, 161, 144, 7, 54, 101, 84, 57, 8, 91, 106, 253, 204, 159, 174, 128, 177, 226, 211, 68, 117, 38, 23, 252, 205, 158, 175, 56, 9, 90, 107, 69, 116, 39, 22, 129, 176, 227, 210, 191, 142, 221, 236, 123, 74, 25, 40, 6, 55, 100, 85, 194, 243, 160, 145, 71, 118, 37, 20, 131, 178, 225, 208, 254, 207, 156, 173, 58, 11, 88, 105, 4, 53, 102, 87, 192, 241, 162, 147, 189, 140, 223, 238, 121, 72, 27, 42, 193, 240, 163, 146, 5, 52, 103, 86, 120, 73, 26, 43, 188, 141, 222, 239, 130, 179, 224, 209, 70, 119, 36, 21, 59, 10, 89, 104, 255, 206, 157, 172};

    /**
     * @brief A class to help access the SHT71 sensor.
     *
     * dataPin and sckPin are OUTPUT by default (after using for INPUT it
     * *MUST* be turned back to OUTPUT).
     *
     * @todo put CRC check into measure!
     * @author peter.vizi@gmail.com
     */
    class SHTxx {
	
    public:
	/**
	 * Create a new object, to communicate with the sensor.
	 *
	 * @param dataPin the pin number used for DATA line
	 * @param sckPin the pin number used for SCK line
	 */
	SHTxx(uint8_t dataPin, uint8_t sckPin);

	/**
	 * Get the temperature in °C.
	 *
	 * @return the temperature
	 */
	float getTemp();
	
	/**
	 * Get the temperature in °F.
	 *
	 * @return the temperature
	 */
	float getTempF();

	/**
	 * Get the average temperature in °C.
	 *
	 * @see _averageLength
	 */
	float getTempAvg();

	/**
	 * Get the average temperature in °F.
	 *
	 * @see _averageLength
	 */
	float getTempAvgF();
	
	/**
	 * Get the humidity in %RH.
	 *
	 * @return the humidity
	 */
	float getHum();

	/**
	 * Get the average humidity.
	 *
	 * @see _averageLength
	 */
	float getHumAvg();
	
    protected:

	/**
	 * 000   0011    0
	 */
	static const float STATUS_REG_W = 0x06;

	/**
	 * 000   0011    1
	 */
	static const float STATUS_REG_R = 0x07;

	/**
	 * 000   0001    1
	 */
	static const float MEASURE_TEMP = 0x03;

	/**
	 * 000   0010    1
	 */
	static const float MEASURE_HUMI = 0x05;

	/**
	 * 000   1111    0
	 */
	static const float RESET        = 0x1e;

	/**
	 * We can ask for temperature and humidity values;
	 */
	enum Sensor {
	    TEMP = 0,
	    HUMI = 1,
	};

	/**
	 * Conversion to engineering units depends on the power supply value.
	 */
	enum VDD {
	    VDD2500mV = 0,
	    VDD3000mV = 1,
	    VDD3500mV = 2,
	    VDD4000mV = 3,
	    VDD5000mV = 4,
	};
	
	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * T = d_1 + d_2 \cdot SO_T
	 * \f]
	 */
	static const float d1TableC[5];

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * T = d_1 + d_2 \cdot SO_T
	 * \f]
	 */
	static const float d1TableF[5];

	/**
	 * The device can sample the temperature with either 14 bits
	 * or 14 bits, the humidity sensor 12 bits or 8 bits.
	 */
	enum Resolution {
	    BITRESLO = 0, // 8/12 bits
	    BITRESHI = 1, // 12/14 bits
	};

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * T = d_1 + d_2 \cdot SO_T
	 * \f]
	 */
	static const float d2TableC[2];

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * T = d_1 + d_2 \cdot SO_T
	 * \f]
	 */
	static const float d2TableF[2];
	
	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * RH_{linear} = c_1+c_2\cdot SO_{RH} + c_3 \cdot SO_{RH}^2
	 * \f]
	 */
	static const float c1Table[2];

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * RH_{linear} = c_1+c_2\cdot SO_{RH} + c_3 \cdot SO_{RH}^2
	 * \f]
	 */
	static const float c2Table[2];

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * RH_{linear} = c_1+c_2\cdot SO_{RH} + c_3 \cdot SO_{RH}^2
	 * \f]
	 */
	static const float c3Table[2];
	
	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * RH_{true} = \left( T_{^\circ C} - 25 \right) \cdot (t_1 + t_2 \cdot SO_{RH}) + RH_{linear}
	 * \f]
	 */
	static const float t1Table[2];

	/**
	 * Constants used for converting into engineering units. Indexed by
	 * VDD2500mV ... VDD5000mV.
	 *
	 * \f[
	 * RH_{true} = \left( T_{^\circ C} - 25 \right) \cdot (t_1 + t_2 \cdot SO_{RH}) + RH_{linear}
	 * \f]
	 */
	static const float t2Table[2];

	/**
	 * The pin number used by the DATA line. This is OUTPUT by
	 * default, when used for INPUT it must be changed.
	 */
	uint8_t _dataPin;

	/**
	 * The pin number used for the SCK line. It is OUTPUT.
	 */
	uint8_t _sckPin;
	
	/**
	 * The Vdd value on the sensor: VDD2500mV, VDD3000mV, VDD3500mV,
	 * VDD4000mV, VDD5000mV.
	 * 
	 * Default: VDD3500mV
	 */
	VDD _vdd;
	
	/**
	 * The used bit resolution: BITRESHI, BITRESLO.
	 *
	 * Default: BITRESHI.
	 */
	Resolution _bitres;
	
	/**
	 * The time when the last temperature measurement was
	 * taken. It is used for avoiding overheating the sensor,
	 * see. Section 3.3 in the datasheet.
	 */
	unsigned long _lastTempMeasurement;
	
	/**
	 * The time when the last humidity measurement was taken. It
	 * is used for avoiding overheating the sensor, see. Section
	 * 3.3 in the datasheet.
	 */
	unsigned long _lastHumMeasurement;

	/**
	 * The number of milliseconds between two measurements. It
	 * is used for avoiding overheating the sensor, see. Section
	 * 3.3 in the datasheet.
	 *
	 * Default: 2000.
	 */
	unsigned long _measurementDelay;
	
	/**
	 * The last measured temperature.
	 */
	uint16_t _temp;

	/**
	 * An array for storing the data to be averaged.
	 */
	uint16_t *_tempAverage;
	
	/**
	 * The lest humidity measurement.
	 */
	uint16_t _hum;

	/**
	 * An array for storing the data to be averaged.
	 */
	uint16_t *_humAverage;

	/**
	 * The number of samples to be averaged.
	 */
	uint8_t _averageLength;

	/**
	 * And index pointing at the last inserted value in the
	 * average array.
	 *
	 * @see _tempAverage, _humAverage
	 */
	uint8_t _averageIndex;
	
	/**
	 * Reset the communication with the sensor.
	 */
	void reset(void);

	/**
	 * Start the communication.
	 */
	void start(void);
	
	/**
	 * Write a byte to the sensor.
	 *
	 * @param value the value to be writen
	 *
	 * @return first bit is 0 if no error 1 if sensor did not ack the
	 * byte
	 */
	uint8_t write(byte value);
	
	/**
	 * Read one byte from the sensor, acknowledgement depends on the parameter.
	 *
	 * @param ack is acknowledgement needed
	 *
	 * @return the data from sensor
	 */
	uint8_t read(bool ack);
	
	/**
	 * Get a measurement from the sensor.
	 *
	 * @param value the measured value
	 * @param checksum the crc
	 * @param mode which sensor to sample TEMP/HUMI
	 *
	 * @return first bit 1 if ack timed out for command, second bint
	 * is 1 if sensor timed out
	 */
	uint8_t measure(uint16_t *value, uint8_t* checksum, Sensor mode);

	/**
	 * Ask for the temperature value.
	 */
	void measureTemp();
	
	/**
	 * Ask for the humidity value.
	 */
	void measureHum();

	/**
	 * Convert the reading from the sensor to °C.
	 *
	 * @param reading the value from the sensor
	 *
	 * @return temperature in engineering units
	 */
	float convertTempC(uint16_t reading);

	/**
	 * Convert the reading from the sensor to °F.
	 *
	 * @param reading the value from the sensor
	 *
	 * @return temperature in engineering units
	 */
	float convertTempF(uint16_t reading);
	
	/**
	 * @param reading the humidity reading from the sensor
	 * @param temp the temperature [°C]
	 *
	 * @return the temperature compensated humidity [%RH]
	 */
	float convertHum(uint16_t reading, float temp);
	
	/**
	 * Calculate the CRC for a received value and check against, the received CRC.
	 *
	 * @param value the value that is received from the sensor
	 * @param recCrc the CRC calculated by the sensor
	 *
	 * @return true if the crc match
	 */
	bool checkCRC(uint16_t value, uint8_t recCrc);

	/**
	 * Calculate the average in an array of values.
	 *
	 * @param array the array storing the values
	 * @param length the number of values
	 *
	 * @return the average
	 */
	uint16_t average(uint16_t* array, uint8_t length);
    };
}

#endif /* SHTXX_H_ */
