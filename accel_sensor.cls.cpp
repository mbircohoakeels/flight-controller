//
//  accel_sensor.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 30/07/2015.
//  This class handles communication too and from the accelerometer (ADXL345)
//

#include "headers/accel_sensor.cls.h"

/*!
 @description Accelerometer Setup - opens a handle to the sensors file
 Sets up an IO CTL to the file, sets the range, resolution
 and offsets. Finally turns the device on.
 @param <none>
 */
ACCEL_SENSOR::ACCEL_SENSOR() {
    this->ACCEL_ADDRESS = 0x19;
    
    if( ( this->i2cHandle = open( "/dev/i2c-1", O_RDWR ) ) < 0 )
        perror( "Setting up file handle for accelerometer failed." );
    
    if( ioctl( this->i2cHandle, I2C_SLAVE, this->ACCEL_ADDRESS ) < 0 )
        perror( "Error connecting to accelerometer." );

    this->set_res_range( HIGHRES_16G );
    this->set_power( ON );
}

/*!
 @function set_power
 - Power switch - ON | OFF
 @params <accel_switch>
 */
void ACCEL_SENSOR::set_power( accel_switch _SWITCH ) {
    this->txBuffer[0] = CTRL_REG1_A;
    this->txBuffer[1] = _SWITCH;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error powering up the accelerometer." );
}

/*!
 @function set_power
 - Power switch - ON | OFF
 @params <accel_switch>
 */
void ACCEL_SENSOR::set_res_range( accel_range _RANGE ) {
    this->txBuffer[0] = CTRL_REG4_A;
    this->txBuffer[1] = _RANGE;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error powering up the accelerometer." );
}


/*!
 @function get_values
 - gets all the registers and stores them in this->rxBuffer
 Assigns all the public variable (X, Y, Z, Range, Res, Angles)
 */
void ACCEL_SENSOR::get_values( void ) {
    this->get_X();
    this->get_Y();
    this->get_Z();
    this->get_current_xy_angle();
}

int ACCEL_SENSOR::writeReg( unsigned char value ) {
    unsigned char buffer[1];
    buffer[0] = value;
    if ( write( this->i2cHandle, buffer, 1 ) != 1 ) {
        perror( "Failed to write to the device\n" );
        return 1;
    }
    return 0;
}

short ACCEL_SENSOR::get_value( unsigned int address ) {
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
 @function get_xy_angles
 - Calculate the X, Y angles based on the current readings.
 */
void ACCEL_SENSOR::get_current_xy_angle( void ) {
    double x2 = 0, y2 = 0, z2 = 0;
    
    this->_X -= OFFSET_X;
    this->_Y += OFFSET_Y;
    
    x2 = this->_X;
    y2 = this->_Y;
    z2 = this->_Z;

    this->roll  = ( atan2 ( (double)-this->_X, (double)this->_Z ) * 180.0 ) / M_PI;
    this->pitch = (( atan2 ( (double)this->_Y, sqrt( (double)this->_X * (double)this->_X + (double)this->_Z * (double)this->_Z ) ) * 180.0 ) / M_PI);
}

void ACCEL_SENSOR::get_xy_angle( void ) {
    int i = 0, total_roll = 0, total_pitch = 0, avg_roll = 0, avg_pitch = 0;
    while (i < 50){
        this->get_values();
        total_roll += this->roll;
        total_pitch += this->pitch;
        avg_roll = total_roll / (i+1);
        avg_pitch = total_pitch / (i+1);
        usleep(2000);
        i++;
    }
    this->roll = avg_roll;
    this->pitch = avg_pitch;
}
/*!
 @function get_X
 - get the current X reading from the sensor
 @returns <short> this->_X
 */
short ACCEL_SENSOR::get_X( void ) { this->_X = ( ( short ) this->get_value( OUT_X_H_A ) << 8 ) | ( short ) this->get_value( OUT_X_L_A ); return this->_X; }//( this->_X = this->_X - OFFSET_X ); }
/*!
 @function get_Y
 - get the current Y reading from the sensor
 @returns <short> this->_Y
 */
short ACCEL_SENSOR::get_Y( void ) { this->_Y = ( ( short ) this->get_value( OUT_Y_H_A ) << 8 ) | ( short ) this->get_value( OUT_Y_L_A ); return this->_Y; }//( this->_Y = this->_Y + OFFSET_Y ); }
/*!
 @function get_Z
 - get the current Z reading from the sensor
 @returns <short> this->_Z
 */
short ACCEL_SENSOR::get_Z( void ) { this->_Z = -( ( short ) this->get_value( OUT_Z_H_A ) << 8 ) | ( short ) this->get_value( OUT_Z_L_A ); return this->_Z; }//( this->_Z = this->_Z + OFFSET_Z ); }
/*!
 @function get_angle_x
 - Return the X angle as a short
 @returns <double> this->x_angle;
 */
double ACCEL_SENSOR::get_roll( void ) { return this->roll; }
/*!
 @function get_angle_y
 - Return the Y angle as a short
 @returns <double> this->y_angle;
 */
double ACCEL_SENSOR::get_pitch( void ) { return this->pitch; }