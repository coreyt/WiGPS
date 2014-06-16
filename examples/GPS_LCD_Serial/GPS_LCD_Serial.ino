/*
 * FILE:    GPS_LCD_Serial.ino
 * PURPOSE: Test GP-635T with LCD and serial output
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
WiGPS gps(Serial1);

/*
 * LCD RS pin to digital pin 23
 * LCD EN pin to digital pin 25
 * LCD D4 pin to digital pin 27
 * LCD D5 pin to digital pin 29
 * LCD D6 pin to digital pin 31
 * LCD D7 pin to digital pin 33
 * LCD RW pin to ground
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(23,25,27,29,31,33);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("GPS starting.");

  lcd.begin(16,2);
  lcd.print("GPS starting.");

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

  // newline between updates
  Serial.print("\n");

  gps.update(3); // attempt update for 3 seconds

  if (gps.isReady() == true) {
    // Serial
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
    Serial.print(gps.getLatitude(),5);
    Serial.print(", ");
    Serial.println(gps.getLongitude(),5);

    // LCD
    /*
    // print data
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(gps.latitude());
    lcd.setCursor(0,1);
    lcd.print(gps.longitude());
    */

    // print data numerically
    // whenever a number is increased by several orders of
    // magnitude, it will overflow and become negative
    // "lat:   +12.45678"
    float lat = gps.getLatitude();
    lcd.setCursor(0,0);
    lcd.print("lat:  ");
    lcd.print(lat >= 0 ? '+' : '-');
    if (abs(lat) < 10.0) {
        lcd.print(' ');
    } else {
        lcd.print((int) floor(abs(lat/10))%10);
    }
    lcd.print((int) floor(abs(lat))%10);
    lcd.print('.');
    lat = lat - ((int) lat);
    lcd.print((int) floor(abs(lat*10))%10);
    lcd.print((int) floor(abs(lat*100))%10);
    lcd.print((int) floor(abs(lat*1000))%10);
    lcd.print((int) floor(abs(lat*10000))%10);
	lat *= 1000000;
    lat = lat - ((int) lat);
    lcd.print((int) floor(abs(lat))%10);
    lcd.print((int) round(abs(lat*10))%10);

    lcd.setCursor(0,1);
    // "long: +123.56789"
    float lon = gps.getLongitude();
    lcd.print("long:");
    lcd.print(lon >= 0 ? '+' : '-');
    if (abs(lon) < 100.0) {
        lcd.print(' ');
    } else {
        lcd.print((int) floor(abs(lon/100))%10);
    }
    if (abs(lon) < 10.0) {
        lcd.print(' ');
    } else {
        lcd.print((int) floor(abs(lon/10))%10);
    }
    lcd.print((int) floor(abs(lon))%10);
    lcd.print('.');
	lon = lon - ((int) lon);
    lcd.print((int) floor(abs(lon*10))%10);
    lcd.print((int) floor(abs(lon*100))%10);
    lcd.print((int) floor(abs(lon*1000))%10);
    lcd.print((int) floor(abs(lon*10000))%10);
	lon *= 1000000;
    lon = lon - ((int) lon);
    lcd.print((int) floor(abs(lon))%10);
    lcd.print((int) round(abs(lon*10))%10);
  } else {
    // Serial
    Serial.println("GPS no data.");

    // LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GPS no data.");
  }
}
