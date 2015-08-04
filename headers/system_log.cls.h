/*!
 *system_log.cls.h Created on: 08/07/2015
 *@author : Michael Brookes
 */

#ifndef SYSTEM_LOG_CLS_H_
#define SYSTEM_LOG_CLS_H_

#include <string>
#include <iostream>

using namespace std;

class SYSTEM_LOG{
private:
    int sys_log_id;
    int sys_id;
    int sys_init_status;
    int sys_current_state;
    
    string sys_session_id;
    string sys_message;
    string sys_data_input_time;
    
public:
    int get_sys_log_id() { return this->sys_log_id; }
    int get_sys_id() { return this->sys_log_id; }
    int get_sys_init_status() { return this->sys_init_status; }
    int get_sys_current_state() { return this->sys_current_state; }
    
    string get_sys_session_id() { return this->sys_session_id; }
    string get_sys_message() { return this->sys_message; }
    string get_sys_data_input_time() { return this->sys_data_input_time; }
};

#endif