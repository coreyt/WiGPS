/*
 * FILE:    GPS_LCD.ino
 * PROGRAM: GPS_LCD
 * PURPOSE: Test GP-635T GPS with LCD
 * AUTHOR:  Geoffrey Card
 *          based on code by Daniele Faugiana
 * DATE:    2014-06-14 -
 * NOTES:
 */

/***************
 * WiGPS Arduino Library
 * Connect the GP-635T module to Arduino
 * Pins are connected as following:
 * VCC: 3.3V, common GND
 * RX - Serial1
 * TX - Serial1
 * Backup battery not connected
 * Power ON/OFF to pin 22
 ***************/
#include <WiGPS.h>
WiGPS gps(22);

#include <LiquidCrystal.h>
LiquidCrystal lcd(23,25,27,29,31,33);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  lcd.begin(16,2);
  lcd.print("Starting.");

  gps.init(22);

  // The GPS will start looking for satellites
  gps.on();

  // Turn off the GPS to save battery without loosing RTC data
  //gps.off();
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  gps.update();

  lcd.clear();
  if (gps.isReady()) {
  	// print data
  	lcd.setCursor(0,0);
    lcd.print(gps.latitude());
  	lcd.setCursor(0,1);
    lcd.print(gps.longitude());
  } else {
  	lcd.setCursor(0,0);
    lcd.print("GPS not ready.");
  }
}
