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
    this->ACCEL_ADDRESS = 0x53;
    
    if( ( this->i2cHandle = open( "/dev/i2c-1", O_RDWR ) ) < 0 )
        perror( "Setting up file handle for accelerometer failed." );
    
    if( ioctl( this->i2cHandle, I2C_SLAVE, this->ACCEL_ADDRESS ) < 0 )
        perror( "Error connecting to accelerometer." );
    
    this->set_res( HIGH );
    this->set_range( R16_G );
    this->save_values();
    this->set_offset(OFSX, -4);
    this->set_offset(OFSY, 4);
    this->set_offset(OFSZ, 9);
    this->set_power( ON );
}

/*!
 @function save_values
 - writes the range and resolution to the sensor.
 @param <none>
 */
void ACCEL_SENSOR::save_values( void ) {
    this->txBuffer[0] = DATA_FORMAT;
    this->txBuffer[1] = 0x00;
    this->txBuffer[1] = this->txBuffer[1] | ( ( this->res ) << 3 );
    this->txBuffer[1] = this->txBuffer[1] | this->range;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error setting range on the accelerometer." );
}

/*!
 @function set_power
 - Power switch - ON | OFF
 @params <accel_switch>
 */
void ACCEL_SENSOR::set_power( accel_switch _SWITCH ) {
    this->txBuffer[0] = POWER_CTL;
    this->txBuffer[1] = _SWITCH;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error powering up the accelerometer." );
}

/*!
 @function set_offset
 - Set the offsets for x, y, z so that they read correctly when static
 @params <unsigned char>, <int8_t>
 */
void ACCEL_SENSOR::set_offset( unsigned char offset_type, int8_t offset ){
    this->txBuffer[0] = offset_type;
    this->txBuffer[1] = offset;
    if( write( this->i2cHandle, this->txBuffer, 2 ) != 2 )
        perror( "Error setting an offset on the accelerometer." );
}

/*!
 @function set_res
 - Save te resolution setting
 @params <accel_res>
 */
void ACCEL_SENSOR::set_res( accel_res res ){ this->res = res; }

/*!
 @function set_range
 - Save te range setting
 @params <accel_range>
 */
void ACCEL_SENSOR::set_range( accel_range range ){ this->range = range; }

/*!
 @function get_values
 - gets all the registers and stores them in this->rxBuffer
   Assigns all the public variable (X, Y, Z, Range, Res, Angles)
 */
void ACCEL_SENSOR::get_values( void ) {
    this->txBuffer[0] = DEVID;
    this->rxBuffer = new unsigned char[TOTAL_REGISTERS];
    write( this->i2cHandle, this->txBuffer, 1 );
    read( this->i2cHandle, this->rxBuffer, TOTAL_REGISTERS );
    this->get_X();
    this->get_Y();
    this->get_Z();
    this->get_res();
    this->get_range();
    this->get_xy_angles();
}

/*!
 @function get_xy_angles
 - Calculate the X, Y angles based on the current readings.
 */
void ACCEL_SENSOR::get_xy_angles( void ) {
    float z_val, x_result, y_result, result;
    unsigned long x2, y2, z2;
    
    z_val = ( float )this->_Z - 256;
    
    x2 = ( unsigned long )( this->_X * this->_X );
    y2 = ( unsigned long )( this->_Y * this->_Y );
    z2 = ( unsigned long )( z_val * z_val );
    
    result = sqrt( y2 + z2 );
    x_result = ( this->_X / result );
    this->x_angle = atan( x_result );
    
    cout << "x2 =" << x2 << " y2 = " << y2 << " z2 = " << z2 << endl;
    cout << "result = " << result << " x_result = " << x_result << " atan(x_result) = " << atan( x_result ) << " this->x_angle = " << this->x_angle << endl;
    
    result = sqrt( x2 + z2 );
    y_result = ( this->_Y / result );
    this->y_angle = atan( y_result );
}

/*!
 @function get_X
 - get the current X reading from the sensor
 @returns <short> this->_X
 */
short ACCEL_SENSOR::get_X( void ) { this->_X = ( ( short ) *( this->rxBuffer + DATAX1 ) << 8 ) | ( short ) *( this->rxBuffer + DATAX0 ); return this->_X; }
/*!
 @function get_Y
 - get the current Y reading from the sensor
 @returns <short> this->_Y
 */
short ACCEL_SENSOR::get_Y( void ) { this->_Y = ( ( short ) *( this->rxBuffer + DATAY1 ) << 8 ) | ( short ) *( this->rxBuffer + DATAY0 ); return this->_Y; }
/*!
 @function get_Z
 - get the current Z reading from the sensor
 @returns <short> this->_Z
 */
short ACCEL_SENSOR::get_Z( void ) { this->_Z = ( ( short ) *( this->rxBuffer + DATAZ1 ) << 8 ) | ( short ) *( this->rxBuffer + DATAZ0 ); return this->_Z; }
/*!
 @function get_angle_x
 - Return the X angle as a short
 @returns <short> this->x_angle;
 */
short ACCEL_SENSOR::get_angle_x( void ) { return this->x_angle; }
/*!
 @function get_angle_y
 - Return the Y angle as a short
 @returns <short> this->y_angle;
 */
short ACCEL_SENSOR::get_angle_y( void ) { return this->y_angle; }
/*!
 @function get_res
 - Return the resolution
 @returns <accel_res> this->res;
 */
ACCEL_SENSOR::accel_res ACCEL_SENSOR::get_res( void ) { this->res = ( accel_res ) ( ( (*( this->rxBuffer + DATA_FORMAT ) ) &0x08 ) >> 3 ); return this->res; }
/*!
 @function get_range
 - Return the range
 @returns <accel_range> this->range;
 */
ACCEL_SENSOR::accel_range ACCEL_SENSOR::get_range( void ) { this->range = ( accel_range ) ( ( *( this->rxBuffer + DATA_FORMAT ) ) &0x03 ); return this->range; }

