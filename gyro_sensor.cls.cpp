//
//  gyro_sensor.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 15/09/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/gyro_sensor.cls.h"

GYRO_SENSOR::GYRO_SENSOR() {
    this->GYRO_ADDRESS = 0x6B;
    
    if( ( this->i2cHandle = open( "/dev/i2c-1", O_RDWR ) ) < 0 )
        perror( "Setting up file handle for gyro failed." );
    
    if( ioctl( this->i2cHandle, I2C_SLAVE, this->GYRO_ADDRESS ) < 0 )
        perror( "Error connecting to gyro." );
    
    this->set_power( ON );
}

/*!
 @function set_power
 - Power switch - ON | OFF
 @params <accel_switch>
 */
void GYRO_SENSOR::set_power( gyro_switch _SWITCH ) {
    this->txBuffer[0] = CTRL1;
    this->txBuffer[1] = _SWITCH;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error powering up the gyro." );
}

/*!
 @function get_values
 - gets all the registers and stores them in this->rxBuffer
 Assigns all the public variable (X, Y, Z, Range, Res, Angles)
 */
void GYRO_SENSOR::get_values( void ) {
    this->get_X();
    this->get_Y();
    this->get_Z();
}

int GYRO_SENSOR::writeReg( unsigned char value ) {
    unsigned char buffer[1];
    buffer[0] = value;
    if ( write( this->i2cHandle, buffer, 1 ) != 1 ) {
        perror( "Failed to write to the device\n" );
        return 1;
    }
    return 0;
}

unsigned char GYRO_SENSOR::get_value( unsigned int address ) {
    if( this->writeReg( address ) != 1 ) {
        unsigned char buff[1];
        if ( read( this->i2cHandle, buff, 1 ) != 1 ) {
            perror( "Failed to read from the device!\n" );
            return 1;
        }
        return buff[0];
    }
    else
        return 1;
}

/*!
 @function get_X
 - get the current X reading from the sensor
 @returns <short> this->_X
 */
short GYRO_SENSOR::get_X( void ) { this->_X = ( ( short ) this->get_value( OUT_X_H ) << 8 ) | ( short ) this->get_value( OUT_X_L ); return (this->_X * 0.017453293F) + 6; }
/*!
 @function get_Y
 - get the current Y reading from the sensor
 @returns <short> this->_Y
 */
short GYRO_SENSOR::get_Y( void ) { this->_Y = ( ( short ) this->get_value( OUT_Y_H ) << 8 ) | ( short ) this->get_value( OUT_Y_L ); return (this->_Y * 0.017453293F) + 6; }
/*!
 @function get_Z
 - get the current Z reading from the sensor
 @returns <short> this->_Z
 */
short GYRO_SENSOR::get_Z( void ) { this->_Z = -( ( short ) this->get_value( OUT_Z_H ) << 8 ) | ( short ) this->get_value( OUT_Z_L ); return (this->_Z * 0.017453293F) - 8; }