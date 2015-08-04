/*!
 *sonic_sensor.cls.h Created on: 24/07/2015
 *@author : Michael Brookes
 */

#include "systems.cls.h"
#include "filehelper.cls.h"

#ifndef SONIC_SENSOR_CLS_H_
#define SONIC_SENSOR_CLS_H_

#define SONIC_MODIFYER 9.8

class SONIC_SENSOR : public SYSTEMS { //inherits from systems

public:
    enum port {
        SONIC_PORT = 0,
    };
    
    int get_sensor_reading();
    
    SONIC_SENSOR( port s_port );
    
private:
    FileHelper FH;
    
    int analog_port;
    int analogReading;
    
    char * buffer;
    
    string sonic_file_loc;
    
    int convert_analog_value( float val );

};

#endif
