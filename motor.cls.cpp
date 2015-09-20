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
    this->load_motor_defaults();
    //int ret1 = pthread_create( &m_thread1, NULL, &MOTOR::thread_function, this );
}

/*!
 @param (none)
 @throws mysql exception
 */
void MOTOR::set_motor_paths( void ) {
    this->period_file_loc = this->get_sys_location().append( "/period" );
    this->duty_file_loc = this->get_sys_location().append( "/duty" );
    this->run_file_loc = this->get_sys_location().append( "/run" );
}

/*!
 This method sets the default values currently configured on the motor.
 This is done in the constructor otherwise all these values are 0;
 @params void
 */
void MOTOR::load_motor_defaults( void ) {
    this->period_val = (int)FH.read_file( this->period_file_loc );
    this->duty_val = (int)FH.read_file( this->duty_file_loc );
    this->run_val = (int)FH.read_file( this->run_file_loc );
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
 Everything looks backwards because the lower the duty val the faster the motor spins.
 @param target_duty<int>
 @throws Exception
 */
void MOTOR::set_duty_val( int td, int motor_num ) {
    this->target_duty = td;
    if ( this->target_duty <= MIN_MOTOR_DUTY && this->target_duty >= MAX_MOTOR_DUTY ){
        if(motor_num == 1){
            this->motor_thread_ret = pthread_create( &this->motor_thread1, NULL, MOTOR::update_duty_val, this );
            if( this->motor_thread_ret ){
                fprintf( stderr, "Error - pthread_create() return code: %d\n",this->motor_thread_ret );
                exit( EXIT_FAILURE );
            }
        }
        if(motor_num == 2){
            this->motor_thread_ret = pthread_create( &this->motor_thread2, NULL, MOTOR::update_duty_val, this );
            if( this->motor_thread_ret ){
                fprintf( stderr, "Error - pthread_create() return code: %d\n",this->motor_thread_ret );
                exit( EXIT_FAILURE );
            }
        }
        if(motor_num == 3){
            this->motor_thread_ret = pthread_create( &this->motor_thread3, NULL, MOTOR::update_duty_val, this );
            if( this->motor_thread_ret ){
                fprintf( stderr, "Error - pthread_create() return code: %d\n",this->motor_thread_ret );
                exit( EXIT_FAILURE );
            }
        }
        if(motor_num == 4){
            this->motor_thread_ret = pthread_create( &this->motor_thread4, NULL, MOTOR::update_duty_val, this );
            if( this->motor_thread_ret ){
                fprintf( stderr, "Error - pthread_create() return code: %d\n",this->motor_thread_ret );
                exit( EXIT_FAILURE );
            }
        }
    }
    else
        cout << "Unable to update the duty value, the duty value must be < or = " << MIN_MOTOR_DUTY << " and > or = " << MAX_MOTOR_DUTY << endl;
        
}

/*
void* MOTOR::thread_function( void *ptr ) {
    printf( "I'm thread ?\n" );
    
    while ( 1 ) {
        cout << "thread global" << endl;
        sleep( 1 );
    }   
}
*/

/*!
 This method is only called by the set_duty_val function - it's purpose is to be a threaded action that increases the speed of the motor without
 interrupting the flow of the program.
 @param target_duty<int>
 */
void* MOTOR::update_duty_val( void *motor_inst ) {
    MOTOR* motor = (MOTOR*)motor_inst;
    while( motor->get_duty_val() < motor->target_duty ) { //decreasing speed
        motor->duty_val = motor->duty_val + SMOOTH_MOTOR_STEP;
        motor->update_system( motor->duty_file_loc, motor->duty_val );
        cout << "Slowing Down : Current Value = " << motor->duty_val << endl;
    }
    
    while( motor->get_duty_val() > motor->target_duty ) { //increasing speed
        motor->duty_val = motor->duty_val - SMOOTH_MOTOR_STEP;
        motor->update_system( motor->duty_file_loc, motor->duty_val );
        cout << "Speeding Up : Current Value = " << motor->duty_val << endl;
    }
    
    if( ( motor->get_duty_val() - motor->target_duty ) < SMOOTH_MOTOR_STEP ) { //finishing off the move if the next jump is less than a smooth step.
        motor->duty_val = motor->target_duty;
        motor->update_system( motor->duty_file_loc, motor->duty_val );
    }
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