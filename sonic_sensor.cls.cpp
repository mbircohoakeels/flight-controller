//
//  sonic_sensor.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 24/07/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/sonic_sensor.cls.h"

SONIC_SENSOR::SONIC_SENSOR( port s_port ) {
    this->analog_port = s_port;
    this->sys_name << "SONIC_INIT";
    this->load_sys_details();
}

int SONIC_SENSOR::convert_analog_value( float val ) {
    return this->analogReading / val;
}

int SONIC_SENSOR::get_sensor_reading() {
    this->buffer = FH.read_file( this->get_sys_location() );
    this->analogReading = atoi(buffer);
    return this->convert_analog_value( SONIC_MODIFYER ); //(see documentation : http://www.maxbotix.com/documents/MB1010_Datasheet.pdf p. 2)
}
