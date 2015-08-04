/*!
 *db_log.cls.h Created on: 08/07/2015
 *@author : Michael Brookes
 */

#ifndef DB_CLS_H_
#define DB_CLS_H_

#define _LOGS_db_username "_LOG_Viewer"
#define _LOGS_db_password "Jt7BcXSbqEVMUuPmzcLrzQ9rKuw"
#define _LOGS_db "_LOGS"
#define _LOGS_db_server "127.0.0.1"

#include <sstream>
#include <mysql++.h>

//#include "db_session.cls.h"

using namespace std;
using namespace mysqlpp;

class DB{

public:
    
    DB();
    
    Connection conn;
    Row row;
    
    StoreQueryResult res;
    StoreQueryResult::const_iterator it;
    
    ostringstream sql_oss;
    
    int open_connection();
    int execute_query( ostringstream &sql_oss );

};

#endif