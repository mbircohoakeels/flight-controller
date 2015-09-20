//
//  MAG_sensor.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 30/07/2015.
//  This class handles communication too and from the accelerometer (ADXL345)
//

#include "headers/mag_sensor.cls.h"

/*!
 @description Accelerometer Setup - opens a handle to the sensors file
 Sets up an IO CTL to the file, sets the range, resolution
 and offsets. Finally turns the device on.
 @param <none>
 */
MAG_SENSOR::MAG_SENSOR() {
    this->MAG_ADDRESS = 0x1E;
    
    if( ( this->i2cHandle = open( "/dev/i2c-1", O_RDWR ) ) < 0 )
        perror( "Setting up file handle for magnetometer failed." );
    
    if( ioctl( this->i2cHandle, I2C_SLAVE, this->MAG_ADDRESS ) < 0 )
        perror( "Error connecting to magnetometer." );

    this->set_mag_rate( 0x94 );
    this->set_mag_conversion( 0x00 );
}

void MAG_SENSOR::set_mag_rate( unsigned char value ) {
    this->txBuffer[0] = CRA_REG_M;
    this->txBuffer[1] = value;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error setting up the magnetometers rate." );
}

void MAG_SENSOR::set_mag_conversion( unsigned char value ) {
    this->txBuffer[0] = MR_REG_M;
    this->txBuffer[1] = value;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error setting up the magnetometers conversion." );
}

/*!
 @function get_values
 - gets all the registers and stores them in this->rxBuffer
 Assigns all the public variable (X, Y, Z, Heading)
 */
void MAG_SENSOR::get_values( void ) {
    this->get_mag_X();
    this->get_mag_Y();
    this->get_mag_Z();
    this->get_heading();
}

int MAG_SENSOR::writeReg( unsigned char value ) {
    unsigned char buffer[1];
    buffer[0] = value;
    if ( write( this->i2cHandle, buffer, 1 ) != 1 ) {
        perror( "Failed to write to the device\n" );
        return 1;
    }
    return 0;
}

unsigned char MAG_SENSOR::get_value( unsigned int address ) {
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

void MAG_SENSOR::get_heading( void ) {
    double x2 = 0, y2 = 0;
    x2 = this->_X;
    y2 = this->_Y;
    
    this->heading = ( atan2 ( x2, y2 ) * 180 ) / M_PI;
    if (this->heading < 0)
        this->heading = 360 + this->heading;
}

short MAG_SENSOR::get_mag_X( void ) { this->_X = ( ( ( short ) this->get_value( OUT_X_H_M ) << 8 ) | ( short ) this->get_value( OUT_X_L_M ) ) /1100; return this->_X; }

short MAG_SENSOR::get_mag_Y( void ) { this->_Y = ( ( ( short ) this->get_value( OUT_X_H_M ) << 8 ) | ( short ) this->get_value( OUT_X_L_M ) ) /1100; return this->_Y; }

short MAG_SENSOR::get_mag_Z( void ) { this->_Z = ( ( ( short ) this->get_value( OUT_Z_H_M ) << 8 ) | ( short ) this->get_value( OUT_Z_L_M ) ) /980; return this->_Z; }
