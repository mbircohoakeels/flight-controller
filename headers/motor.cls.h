/*!
 *motor.cls.h Created on: 08/07/2015
 *@author : Michael Brookes
 */

#ifndef MOTOR_CLS_H_
#define MOTOR_CLS_H_

#include <string>

#include "systems.cls.h"
#include "filehelper.cls.h"

using namespace std;

#define LOWEST_MOTOR_DUTY 230000 //low throttle val (non spinning).
#define SLOWEST_MOTOR_DUTY 200000 //slowest motor speed (slow spinning).
#define FASTEST_MOTOR_DUTY 15000 //fastest speed the motor can go (fast spinning).

class MOTOR : public SYSTEMS { //inherits from systems

public:
    
    enum run_eval {
        ON = 1,
        OFF = 0,
    };
    
    enum period_eval {
        ACTIVE = 1350000,
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
        STOP = 230000,
        SLOW = 200000,
        FAST = 15000,
    };
    
    int get_pnum() { return this->pnum; }
    int get_pblock() { return this->pblock; }
    int get_duty_val() { return this->duty_val; }
    
    void set_duty_val( int val );
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
    
    void set_pnum( int val ) { this->pnum = val; }
    void set_pblock( int val ) { this->pblock = val; }
    
    void set_motor_paths();
    void update_system( string file_loc, int val );
    
    FileHelper FH;
    
};

#endif