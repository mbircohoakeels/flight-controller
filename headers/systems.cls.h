/*!
 *systems.cls.h Created on: 08/07/2015
 *@author : Michael Brookes
 */

#ifndef SYSTEMS_CLS_H_
#define SYSTEMS_CLS_H_

#include <string>
#include <iostream>

#include "db.cls.h"

using namespace std;

class SYSTEMS : protected DB {
    
private:
    
public:
    
    SYSTEMS();
    
    ostringstream sql_query;
    
    int sys_id;
    
    ostringstream sys_name;
    ostringstream sys_location;

    void load_sys_details();
    
    void set_sys_name( string val ) { this->sys_name << val; }
    
    int get_sys_id() { return this->sys_id; }
    
    string get_sys_name() { return this->sys_name.str(); }
    string get_sys_location() { return this->sys_location.str(); }
    
};

#endif