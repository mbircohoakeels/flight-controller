//
//  motor.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 18/07/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/motor.cls.h"

/*!
 @param int block (Motor Pin Block Number)
 @param int pin (Pin Number Used on Block)
 */
MOTOR::MOTOR( pwm_block block, pwm_pin pin ) : SYSTEMS(){
    this->set_pblock( block );
    this->set_pnum( pin );
    this->sys_name << "PWM_" << block << "_" << pin << "_INIT";
    this->load_sys_details();
    this->set_motor_paths();
}

/*!
 @param (none)
 @throws mysql exception
 */
void MOTOR::set_motor_paths() {
    this->period_file_loc = this->get_sys_location().append("/period");
    this->duty_file_loc = this->get_sys_location().append("/duty");
    this->run_file_loc = this->get_sys_location().append("/run");
}

/*!
 @param val<run_eval>
 @throws Exception
 */
void MOTOR::set_run_val( run_eval val ) {
    this->run_val = val;
    this->update_system( this->run_file_loc, this->run_val );
}

/*!
 @param val<period_eval>
 @throws Exception
 */
void MOTOR::set_period_val( period_eval val ) {
    this->period_val = val;
    this->update_system( this->period_file_loc, this->period_val );
}

/*!
 Duty is the motor speed - this ranges from 15000 to 230000 the lower = the faster
 @param val<int>
 @throws Exception
 */
void MOTOR::set_duty_val( int val ) {
    if ( val <= LOWEST_MOTOR_DUTY && val >= FASTEST_MOTOR_DUTY ){
        this->duty_val = val;
        this->update_system( this->duty_file_loc, this->duty_val );
    }
    else
        cout << "Unable to update the duty value, the duty value must be < or = " << LOWEST_MOTOR_DUTY << " and > or = " << FASTEST_MOTOR_DUTY << endl;
        
}

/*!
 This method is used to update the system file with the value passed.
 @param file_loc<string>
 @param val<int>
 @throws Exception
 */
void MOTOR::update_system( string file_loc, int val ) {
    try{
        FH.update_file_int( file_loc, val ); //write the new value to the device/period file.
    }
    catch (int e){
        cout << "An error occured when updating the file : " << file_loc << " with the value : " << val << endl;
        cout << "The error thrown is : " << e << endl; //show an error to the user.
    }
}