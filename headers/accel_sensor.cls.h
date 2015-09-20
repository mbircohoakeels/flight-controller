/*!
 *accel_sensor.cls.h Created on: 30/07/2015
 *@author : Michael Brookes
 */

#ifndef ACCEL_SENSOR_CLS_H_
#define ACCEL_SENSOR_CLS_H_

#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

//From Table 17. of the LSM303 Data sheet ( https://www.adafruit.com/datasheets/LSM303DLHC.PDF )
//Accelerometer
#define CTRL_REG1_A         0x20    //Read/Write (power control)
#define CTRL_REG2_A         0x21    //Read/Write
#define CTRL_REG3_A         0x22    //Read/Write
#define CTRL_REG4_A         0x23    //Read/Write
#define CTRL_REG5_A         0x24    //Read/Write
#define CTRL_REG6_A         0x25    //Read/Write
#define REFERENCE_A         0x26    //Read/Write
#define STATUS_REG_A        0x27    //Read
#define OUT_X_L_A           0x28    //Read
#define OUT_X_H_A           0x29    //Read
#define OUT_Y_L_A           0x2A    //Read
#define OUT_Y_H_A           0x2B    //Read
#define OUT_Z_L_A           0x2C    //Read
#define OUT_Z_H_A           0x2D    //Read
#define FIFO_CTRL_REG_A     0x2E    //Read/Write
#define FIFO_SRC_REG_A      0x2F    //Read
#define INT1_CFG_A          0x30    //Read/Write
#define INT1_SOURCE_A       0x31    //Read
#define INT1_THS_A          0x32    //Read/Write
#define INT1_DURATION_A     0x33    //Read/Write
#define INT2_CFG_A          0x34    //Read/Write
#define INT2_SOURCE_A       0x35    //Read
#define INT2_THS_A          0x36    //Read/Write
#define INT2_DURATION_A     0x37    //Read/Write
#define CLICK_CFG_A         0x38    //Read/Write
#define CLICK_SRC_A         0x39    //Read/Write
#define CLICK_THS_A         0x3A    //Read/Write
#define TIME_LIMIT_A        0x3B    //Read/Write
#define TIME_LATENCY_A      0x3C    //Read/Write
#define TIME_WINDOW_A       0x3D    //Read/Write

#define OFFSET_X            25.5     //average of 2000 iterations on a flat floor not moving.
#define OFFSET_Y            13    // as above

class ACCEL_SENSOR {

private:
    
    enum accel_switch {
        ON = 0x77,
        OFF = 0x00
    };
    
    enum accel_range {
        HIGHRES_16G = 0x38,
        LOWRES_2G   = 0x00
    };
    
    char txBuffer[2];
    
    int ACCEL_ADDRESS;
    int openi2cStatus;
    int i2cHandle;
    
    short get_value(unsigned int address);
    
    void get_current_xy_angle( void );
    void get_values( void );
    
    int writeReg(unsigned char value);

    void set_power( accel_switch _SWITCH );
    void set_res_range( accel_range _RANGE );
    
public:
    
    short _X;
    short _Y;
    short _Z;
    double roll;
    double pitch;
    
    ACCEL_SENSOR();
    
    void get_xy_angle( void );
    short get_X( void );
    short get_Y( void );
    short get_Z( void );
    double get_roll( void );
    double get_pitch( void );
    
};

#endif