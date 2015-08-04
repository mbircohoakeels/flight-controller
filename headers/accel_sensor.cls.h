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

//From Table 19. of the ADXL345 Data sheet ( http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf )
#define DEVID           0x00   //Device ID                                                   - Read Only.
#define THRESH_TAP      0x1D   //Tap Threshold                                               - Read/Write Available.
#define OFSX            0x1E   //X-axis Offset                                               - Read/Write Available.
#define OFSY            0x1F   //Y-axis Offset                                               - Read/Write Available.
#define OFSZ            0x20   //Z-axis Offset                                               - Read/Write Available.
#define DUR             0x21   //Tap duration                                                - Read/Write Available.
#define LATENT          0x22   //Tap latency                                                 - Read/Write Available.
#define WINDOW          0x23   //Tap window                                                  - Read/Write Available.
#define THRESH_ACT      0x24   //Activity threshold                                          - Read/Write Available.
#define THRESH_INACT    0x25   //Threshold inactivity                                        - Read/Write Available.
#define TIME_INACT      0x26   //Inactivity time                                             - Read/Write Available.
#define ACT_INACT_CTL   0x27   //Axis enable control for activity and inactivity detection   - Read/Write Available.
#define THRESH_FF       0x28   //Free-fall threshold                                         - Read/Write Available.
#define TIME_FF         0x29   //Free-fall time                                              - Read/Write Available.
#define TAP_AXES        0x2A   //Axis control for single tap/double tap                      - Read/Write Available.
#define ACT_TAP_STATUS  0x2B   //Source of single tap/double tap                             - Read Only.
#define BW_RATE         0x2C   //Data rate and power mode control                            - Read/Write Available.
#define POWER_CTL       0x2D   //Power-saving features control                               - Read/Write Available.
#define INT_ENABLE      0x2E   //Interrupt enable control                                    - Read/Write Available.
#define INT_MAP         0x2F   //Interrupt mapping control                                   - Read/Write Available.
#define INT_SOURCE      0x30   //Source of interrupts                                        - Read Only.
#define DATA_FORMAT     0x31   //Data format control                                         - Read/Write Available.
#define DATAX0          0x32   //X-axis Data 0                                               - Read Only.
#define DATAX1          0x33   //X-axis Data 1                                               - Read Only.
#define DATAY0          0x34   //Y-axis Data 0                                               - Read Only.
#define DATAY1          0x35   //Y-axis Data 1                                               - Read Only.
#define DATAZ0          0x36   //Z-axis Data 0                                               - Read Only.
#define DATAZ1          0x37   //Z-axis Data 1                                               - Read Only.
#define FIFO_CTL        0x38   //FIFO control                                                - Read/Write Available.
#define FIFO_STATUS     0x39   //FIFO status                                                 - Read Only
#define TOTAL_REGISTERS 0x40

class ACCEL_SENSOR {

private:
    
    enum accel_switch {
        ON = 0x08,
        OFF = 0x00
    };
    
    enum accel_range {
        R2_G = 0,
        R4_G = 1,
        R8_G = 2,
        R16_G = 3
    };
    
    enum accel_res {
        STANDARD = 0,
        HIGH = 1
    };
    
    unsigned char* rxBuffer;
    char txBuffer[2];
    
    int ACCEL_ADDRESS;
    int openi2cStatus;
    int i2cHandle;
    
    void get_xy_angles( void );
    
    accel_range get_range( void );
    accel_res get_res( void );
    
    void save_values( void );
    void set_power( accel_switch _SWITCH );
    void set_range( accel_range range );
    void set_res( accel_res res );
    void set_offset( unsigned char offset_type, int8_t offset );
    
public:
    
    short _X;
    short _Y;
    short _Z;
    short x_angle;
    short y_angle;
    
    accel_range range;
    accel_res res;
    
    ACCEL_SENSOR();
    
    void get_values( void );
    
    short get_X( void );
    short get_Y( void );
    short get_Z( void );
    short get_angle_x( void );
    short get_angle_y( void );
};

#endif