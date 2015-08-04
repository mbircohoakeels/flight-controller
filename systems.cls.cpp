//
//  systems.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 18/07/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/systems.cls.h"

SYSTEMS::SYSTEMS() : DB() {}

void SYSTEMS::load_sys_details(){
    this->sql_query << "SELECT * FROM `_SYSTEMS` WHERE `system_name` = '" << this->sys_name.str() << "';";
    this->execute_query( this->sql_query );
    for (this->it = this->res.begin(); this->it != this->res.end(); ++this->it) {
        this->row = *this->it;
        this->sys_id = this->row[0];
        this->sys_name << this->row[1];
        this->sys_location << this->row[2];
    }

}