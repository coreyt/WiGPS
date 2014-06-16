/*
 Copyright 2013 Daniele Faugiana

 This file is part of "WiGPS Arduino Library".

 "WiGPS Arduino Library" is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 "WiGPS Arduino Library" is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with "WiGPS Arduino Library". If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * MODIFIED BY:   Geoffrey Card
 * FILE:          WiGPS.h
 * PROGRAM:       rover
 * PURPOSE:       collect and convert NMEA GPS data
 * DATE:          2014-06-14 -
 * NOTES:         Arduino doubles are floats
 * MODIFICATIONS: Converted to Arduino IDE
 *                Used m/s instead of km/h
 *                Fixed latitude and longitude seconds
 *                Added get functions
 *                Formatted to YYYY-MM-DD HH:mm:ss
 *                Added seconds as float for more precision
 *                Update loop exits on timeout
 *                Serial selection in constructor
 */

#ifndef _WIGPS_H
#define _WIGPS_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "GPRMC.h"

/*****************
 * Data constants
 *****************/

#define DEFAULT_UPDATE_TIMEOUT 5 // attempt update for 5 seconds
#define CONV_TO_SEC 0.0006 // converts sub-1 minutes to seconds 0.mmmmm -> ss
#define KNOTS_TO_MS 0.514444 // knots to m/s
#define DEGREE_CHAR 0xDF // Hitachi degree
#define PROTOCOL "GPRMC"
#define BUFFER_LENGTH_2 75 //Had to change the name because made conflict with some other SparkCore define named BUFFER_LENGTH

/*******************
 * GPS POWER STATES
 *******************/

#define ON  1
#define OFF 0

/*************
 * TYPEDEFS
 *************/

typedef unsigned int uint;
typedef unsigned char uchar;

class WiGPS {

private:

    /***************
     * PRIVATE VARS
     ***************/

    HardwareSerial& _serial;

    uint powerPort;             // The pin Arduino uses to activate/deactivate the GPS
    bool powerState;            // Power state of the GPS

    int hours;                  // Last UTC time data from the GPS
    int minutes;
    int seconds;

    int day;                    // Last UTC date data from the GPS
    int month;
    int year;

    int latitudeDeg;            // Last Latitude data from the GPS
    int latitudeMin;
    int latitudeSec;
    float latitudeSecf;         // Seconds as a float, for more precision
    char latitudeRef;

    int longitudeDeg;           // Last Longitude data from the GPS
    int longitudeMin;
    int longitudeSec;
    float longitudeSecf;        // Seconds as a float, for more precision
    char longitudeRef;

    int Speed;                  // Last speed from the GPS (km/h)
    int Course;                 // Last course over ground (degrees from the north)

    bool dataReady;             // Data ready to be read

    /******************
     * PRIVATE METHODS
     ******************/

    void parseGPRMC(GPRMC*);        // Extract data from the GPRMC String

public:

    /*****************
     * PUBLIC METHODS
     *****************/

    WiGPS(HardwareSerial& serial);
    void init(int);

    int on(void);                   // Powers on the GPS module
    int off(void);                  // Turns off the GPS module and stop tracking data
    bool update(void);              // Starts fetching data from the GPS.
    bool update(int timeout_sec);   // Starts fetching data from the GPS.

    String time(void);              // Returns an Arduino String object for the UTC time
    String date(void);              // Returns an Arduino String object for the UTC date
    String latitude(void);          // Returns an Arduino String object for the latitude
    String longitude(void);         // Returns an Arduino String object for the longitude
    String speed(void);             // Returns an Arduino String object for the speed
    String course(void);            // Returns an Arduino String object for the course

    bool isReady(void);             // Returns dataReady, use to determine whether to read

    float getLatitude(void);        // Returns a float for the latitude in degrees
    int getLatitudeDeg(void);       // Last Latitude data from the GPS
    int getLatitudeMin(void);
    int getLatitudeSec(void);
    float getLatitudeSecf(void);
    char getLatitudeRef(void);

    float getLongitude(void);       // Returns a float for the latitude in degrees
    int getLongitudeDeg(void);      // Last Longitude data from the GPS
    int getLongitudeMin(void);
    int getLongitudeSec(void);
    float getLongitudeSecf(void);
    char getLongitudeRef(void);

    ~WiGPS();
};

#endif // _WIGPS_H
