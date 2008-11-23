//****************************************************************
/*
 * Watchdog Sleep Example 
 * Demonstrate the Watchdog and Sleep Functions
 * Photoresistor on analog0 Piezo Speaker on pin 10
 * 
 
 * KHM 2008 / Lab3/  Martin Nawrath nawrath@khm.de
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne
 
 */
//****************************************************************

#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int nint;
int pinLed=13;
int pinPiezoSpeaker=10;

volatile boolean f_wdt=1;

void setup(){

  Serial.begin(38400);
  pinMode(pinLed,OUTPUT);
  pinMode(pinPiezoSpeaker,OUTPUT);
  Serial.println("nightingale");

  // CPU Sleep Modes 
  // SM2 SM1 SM0 Sleep Mode
  // 0    0  0 Idle
  // 0    0  1 ADC Noise Reduction
  // 0    1  0 Power-down
  // 0    1  1 Power-save
  // 1    0  0 Reserved
  // 1    0  1 Reserved
  // 1    1  0 Standby(1)

  cbi( SMCR,SE );      // sleep enable, power down mode
  cbi( SMCR,SM0 );     // power down mode
  sbi( SMCR,SM1 );     // power down mode
  cbi( SMCR,SM2 );     // power down mode

  setup_watchdog(7);
}

byte del;
int cnt;
byte state=0;
int light=0;


//****************************************************************
//****************************************************************
//****************************************************************
void loop(){


  if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;       // reset flag

    light=analogRead(0);  // reading photoresistor
   
    Serial.print("light: " );
    Serial.println(light );

    switch (state){
    case 0:     // waiting for dawn
      if (light < 500) {  // light threshold
        state=1;
      }
      break;
    case 1:  // waiting for dusk
      if (light > 800)  { // light threshold
        state=0;
        whistle();
      }
      break;
    }

    nint++;
    digitalWrite(pinLed,1);  // let led blink

    Serial.print("Sleep " );
    Serial.println(nint );
    delay(2);               // wait until the last serial character is send
    digitalWrite(pinLed,0);


    pinMode(pinLed,INPUT); // set all used port to intput to save power
    pinMode(pinPiezoSpeaker,INPUT); // set all used port to intput to save power

    system_sleep();

    pinMode(pinLed,OUTPUT); // set all ports into state before sleep
    pinMode(pinPiezoSpeaker,OUTPUT); // set all ports into state before sleep


  }

}
//****************************************************************  
// put some whiste sound on piezo
void whistle() {
for (int ii = 0; ii<= 20; ii++) {  
  for (del=0; del <=254; del++) {
  digitalWrite(pinPiezoSpeaker,0);
  delayMicroseconds((ii*5)+(del * 2));
  digitalWrite(pinPiezoSpeaker,1);
  delayMicroseconds((ii*5)+(del * 2));
  }
  PORTB ^= 32;  // toggle pinLed
}
  
}

//****************************************************************  
// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {

  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

    sleep_disable();                     // System continues execution here when watchdog timed out 
    sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON

}

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
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
//****************************************************************  
// Watchdog Interrupt Service / is executed when  watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}

