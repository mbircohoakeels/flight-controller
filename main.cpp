//
//  main.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 09/07/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/motor.cls.h"
#include "headers/sonic_sensor.cls.h"
#include "headers/accel_sensor.cls.h"
#include "headers/mag_sensor.cls.h"
#include "headers/gyro_sensor.cls.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main() {
    /*
     Initialise MOTOR 1 and set default values
     Run Val = 1
     Period Val = 1350000
     Duty Val = 230000
     */
    MOTOR _MOTOR_1( _MOTOR_1.P9, _MOTOR_1.PWM42 );
    _MOTOR_1.set_run_val( _MOTOR_1.ON );
    _MOTOR_1.set_period_val( _MOTOR_1.ACTIVE );
    //_MOTOR_1.set_duty_val ( _MOTOR_1.STOP );
    _MOTOR_1.set_duty_val( 430000, 1 );
    /*
     End MOTOR 1 Initialisation.
     */
    
    /*
     Initialise MOTOR 2 and set default values
     Run Val = 1
     Period Val = 1350000
     Duty Val = 230000
     */
    MOTOR _MOTOR_2( _MOTOR_2.P8, _MOTOR_2.PWM19 );
    _MOTOR_2.set_run_val( _MOTOR_2.ON );
    _MOTOR_2.set_period_val( _MOTOR_2.ACTIVE );
    //_MOTOR_2.set_duty_val( _MOTOR_2.STOP );
    _MOTOR_2.set_duty_val( 430000, 2 );
    /*
     End MOTOR 2 Initialisation.
     */
    
    /*
     Initialise MOTOR 3 and set default values
     Run Val = 1
     Period Val = 1350000
     Duty Val = 230000
     */
    MOTOR _MOTOR_3( _MOTOR_3.P9, _MOTOR_3.PWM14 );
    _MOTOR_3.set_run_val( _MOTOR_3.ON );
    _MOTOR_3.set_period_val( _MOTOR_3.ACTIVE );
    //_MOTOR_3.set_duty_val ( _MOTOR_3.STOP );
    _MOTOR_3.set_duty_val( 430000, 3 );
    /*
     End MOTOR 3 Initialisation.
     */
    
    /*
     Initialise MOTOR 4 and set default values
     Run Val = 1
     Period Val = 1350000
     Duty Val = 230000
     */
    MOTOR _MOTOR_4( _MOTOR_4.P9, _MOTOR_4.PWM22 );
    _MOTOR_4.set_run_val( _MOTOR_4.ON );
    _MOTOR_4.set_period_val( _MOTOR_4.ACTIVE );
    //_MOTOR_4.set_duty_val( _MOTOR_4.STOP );
    _MOTOR_4.set_duty_val( 430000, 4 );
    /*
     End MOTOR 4 Initialisation.
     */
    
    /*
     Initialise the Sonic Sensor on Analog Port 0
     */
    SONIC_SENSOR _SONIC_( _SONIC_.SONIC_PORT );
    /*
     End of Sonic Sensor Initialisations
     */
    
    /*
     Initialise the Accelerometer Sensor
     */
    ACCEL_SENSOR _ACCEL_;
    /*
     End of Accelerometer Initialisations
     */
    
    /*
     Initialise the Magnetometer Sensor
     */
    MAG_SENSOR _MAG_;
    /*
     End of Magnetometer Initialisations
     */
    
    /*
     Initialise the Gyro Sensor
     */
    GYRO_SENSOR _GYRO_;
    /*
     End of Gyro Initialisations
     */
    
    int counter = 0;
    
    while(1){
        
        if( counter == 20 ){
            _MOTOR_1.set_duty_val ( _MOTOR_1.STOP, 1 );
            _MOTOR_2.set_duty_val ( _MOTOR_2.STOP, 2 );
            _MOTOR_3.set_duty_val ( _MOTOR_3.STOP, 3 );
            _MOTOR_4.set_duty_val ( _MOTOR_4.STOP, 4 );
        }
        
        _ACCEL_.get_xy_angle();
        
        counter++;
        cout << endl << "Counter = " << counter << endl;

    }
}