/**
 * @file
 * @brief Moodlight application.
 *
 * Using three LEDs this application shows different colours.
 */

/**
 * The pin number of the green LED.
 */
int greenPin = 13;

/**
 * The pin number of the red LED.
 */
int redPin = 12;

/**
 * The pin number of the blue LED.
 */
int bluePin = 11;

/**
 * Set the pins as output.
 */
void setup() {
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

/**
 * Change color.
 */
void loop() {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(1500);
}
