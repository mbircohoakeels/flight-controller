//
//  mag_sensor.cls.h
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 15/09/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#ifndef __QuadCopterTakeOff__mag_sensor_cls__
#define __QuadCopterTakeOff__mag_sensor_cls__

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
//Magnetometer
#define CRA_REG_M           0x00    //Read/Write
#define CRB_REG_M           0x01    //Read/Write
#define MR_REG_M            0x02    //Read/Write
#define OUT_X_H_M           0x03    //Read
#define OUT_X_L_M           0x04    //Read
#define OUT_Z_H_M           0x05    //Read
#define OUT_Z_L_M           0x06    //Read
#define OUT_Y_H_M           0x07    //Read
#define OUT_Y_L_M           0x08    //Read
#define SR_REG_Mg           0x09    //Read
#define IRA_REG_M           0x0A    //Read
#define IRB_REG_M           0x0B    //Read
#define IRC_REG_M           0x0C    //Read
#define TEMP_OUT_H_M        0x31    //Read
#define TEMP_OUT_L_M        0x32    //Read

class MAG_SENSOR {
    
private:
    
    char txBuffer[2];

    int MAG_ADDRESS;
    int openi2cStatus;
    int i2cHandle;
    
    unsigned char get_value(unsigned int address);
    
    void set_mag_rate( unsigned char value );
    void set_mag_conversion( unsigned char value );
    
    int writeReg(unsigned char value);
    
public:
    
    short _X;
    short _Y;
    short _Z;
    
    MAG_SENSOR();
    
    void get_values( void );
    void get_heading( void );
    
    double heading;
    
    short get_mag_X( void );
    short get_mag_Y( void );
    short get_mag_Z( void );
    
};

#endif /* defined(__QuadCopterTakeOff__mag_sensor_cls__) */