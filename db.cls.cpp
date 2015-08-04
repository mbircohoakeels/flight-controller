//
//  db.cls.cpp
//  QuadCopterTakeOff
//
//  Created by Michael Brookes on 18/07/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/db.cls.h"

DB::DB(){
    this->open_connection();
}

/*!
 @function openConnection.
 - Opens a connection to the db.
 @private Available only to this class.
 @return int (1 Success, -1 error).
 */
int DB::open_connection() {
    try {
        this->conn.connect( _LOGS_db, _LOGS_db_server, _LOGS_db_username, _LOGS_db_password );
        return 1;
    } catch ( const ConnectionFailed& e ) {
        cout << "An Exception Occured : " << e.what() << endl;
        return -1;
    }
}

/*!
 @function executeQuery
 - Runs a query on this objects current DB connection.
 @public Available to other objects that initialise this class.
 @param sql_str<string> The full sql query to run.
 @throws MySQL Exception
 @return StoreQueryResult
 */
int DB::execute_query( ostringstream &sql_oss ) {
    try {
        Query query = this->conn.query( sql_oss.str() );
        if ( this->res = query.store() ){
            sql_oss.str("");
            return 1;
        }
    }
    catch ( const BadQuery& e) {
        cerr << "Bad Query " << e.what() << endl << sql_oss.str() << endl;
    }
    catch ( const BadParamCount& e) {
        cerr << "Incorrect Number Of Params " << e.what() << endl;
    }
    catch ( const BadInsertPolicy& e) {
        cerr << "Bad Insert Policy " << e.what() << endl;
    }
    catch ( const BadFieldName& e) {
        cerr << "FieldName doesn't exist " << e.what() << endl;
    }
    catch ( const Exception& e) {
        cerr << "Error : " << e.what() << endl;
    }
}