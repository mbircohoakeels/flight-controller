/*!
 *gyro_sensor.cls.h Created on: 15/09/2015
 *@author : Michael Brookes
 */

#ifndef GYRO_SENSOR_CLS_H_
#define GYRO_SENSOR_CLS_H_

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

//From Table 17. of the L3GD20H Data sheet
#define CTRL1       0x20
#define OUT_X_L     0x28
#define OUT_X_H     0x29
#define OUT_Y_L     0x2A
#define OUT_Y_H     0x2B
#define OUT_Z_L     0x2C
#define OUT_Z_H     0x2D

class GYRO_SENSOR {

private:
    
    enum gyro_switch {
        ON = 0x7F,
        OFF = 0x00
    };
    
    char txBuffer[2];
    
    int GYRO_ADDRESS;
    int openi2cStatus;
    int i2cHandle;
    
    unsigned char get_value(unsigned int address);
    
    int writeReg(unsigned char value);
    
    void set_power( gyro_switch _SWITCH );

public:
    short _X;
    short _Y;
    short _Z;
    
    GYRO_SENSOR();
    
    void get_values( void );
    
    short get_X( void );
    short get_Y( void );
    short get_Z( void );
    
};

#endif