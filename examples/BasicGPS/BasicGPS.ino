//#include "application.h"
// This #include statement was automatically added by the Spark IDE.
#include <WiGPS.h>

// This #include statement was automatically added by the Spark IDE.
#include <GPRMC.h>

/***************
 * WiGPS Arduino Library, BasicGPS example.
 * Connect the GPS-11571 module to your SparkCore
 * Pins are connected as following:
 * VCC: 3.3V, common GND
 * RX - Serial1
 * TX - Serial1
 * Backup battery not connected
 * Power ON/OFF to pin 7
 ***************/

// Initialize a new WiGPS object
#define GPS_EN_PIN 7
WiGPS gps(GPS_EN_PIN);

void setup() {
  
  gps.init(GPS_EN_PIN);
  // You will inspect values trough the Serial Port
  Serial.begin(9600);
  
  // The GPS will start looking for satellites
  gps.on();
  delay(3000);
  Serial.println("Please wait...");
  
  // Turn off the GPS to save battery without loosing RTC data
  //gps.off();
}

void loop() {
  
  gps.update();
   
  // After data have been retrieved you'll get them
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

  delay(3000);
}
