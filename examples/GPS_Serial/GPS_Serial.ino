/*
 * FILE:    GPS_Serial.ino
 * PROGRAM: GPS_test
 * PURPOSE: test GP-635T GPS
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

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("Starting.");

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

  // newline between updates
  Serial.print("\n");
  if (gps.isReady()) {
	// print all data
	Serial.print("Time: ");
	Serial.println(gps.time());
	Serial.print("Date: ");
	Serial.println(gps.date());
	Serial.print("Latitude: ");
	Serial.println(gps.latitude());
	Serial.print("Longitude: ");
	Serial.println(gps.longitude());
	Serial.print("Speed: ");
	Serial.println(gps.speed());
	Serial.print("Course: ");
	Serial.println(gps.course());

	// print numerical data
	Serial.println("Numerical Lat & Long: ");
    Serial.println(gps.getLatitude());
    Serial.println(gps.getLongitude());
  } else {
    Serial.println("GPS not ready.");
  }
}
