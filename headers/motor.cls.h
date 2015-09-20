/*!
 *motor.cls.h Created on: 08/07/2015
 *@author : Michael Brookes
 */

#ifndef MOTOR_CLS_H_
#define MOTOR_CLS_H_

#include <pthread.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "systems.cls.h"
#include "filehelper.cls.h"

using namespace std;

#define SLOWEST_MOTOR_DUTY 200000 //slowest motor speed (slow spinning).
#define MIN_MOTOR_DUTY 1500000 //low throttle val (non spinning).
#define MAX_MOTOR_DUTY 15000 //fastest speed the motor can go (fast spinning).
#define SMOOTH_MOTOR_STEP 500 //increase or decrease the duty by this much for smooth transition
#define URGENT_MOTOR_STEP 1000 //increase to the target duty much quicker.

class MOTOR : public SYSTEMS { //inherits from systems

public:
    
    enum run_eval {
        ON = 1,
        OFF = 0,
    };
    
    enum period_eval {
        ACTIVE = 1900000,
        INACTIVE = 0,
    };
    
    enum pwm_block {
        P9 = 9,
        P8 = 8,
    };
    
    enum pwm_pin {
        PWM42 = 42,
        PWM22 = 22,
        PWM19 = 19,
        PWM14 = 14,
    };
    
    enum motor_speeds {
        STOP = 780000,
        SLOW = 700000,
        FAST = 150000,
        TAKEOFF = 250000, //no batteries
    };
    
    int get_pnum() { return this->pnum; }
    int get_pblock() { return this->pblock; }
    int get_duty_val() { return this->duty_val; }
    int get_target_duty() { return this->target_duty; }
    
    void set_duty_val( int td, int motor_num );
    void set_run_val( run_eval val );
    void set_period_val( period_eval val );
    
    int get_period_val() const { return this->period_val; }
    int get_run_val() const { return this->run_val; }
    
    string period_file_loc;
    string duty_file_loc;
    string run_file_loc;
    
    MOTOR( pwm_block block, pwm_pin pin );
    
private:
    
    int pnum;
    int pblock;
    int run_val;
    int duty_val;
    int period_val;
    int target_duty;
    int motor_thread_ret;
    
    void set_pnum( int val ) { this->pnum = val; }
    void set_pblock( int val ) { this->pblock = val; }
    
    void set_motor_paths( void );
    void load_motor_defaults( void );
    void update_system( string file_loc, int val );
    static void* update_duty_val( void *motor_inst );
    
    //static void* thread_function( void *ptr );
    //pthread_t m_thread1, m_thread2;
    
    pthread_t motor_thread1, motor_thread2, motor_thread3, motor_thread4;
    
    FileHelper FH;
    
};

#endif