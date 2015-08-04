//
//  FileHelper.h
//  QuadCopter
//
//  Created by Michael Brookes on 30/03/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#ifndef QuadCopter_FileHelper_h
#define QuadCopter_FileHelper_h
#define MAX_BUF 1024

#include <string>
#include <stdio.h> //for (fopen, snprintf)
#include <iostream> //for (cout, endl)
#include <stdlib.h>

using namespace std;

class FileHelper {
    
public:
    FileHelper();
    int file_exists( string FH_Name );
    int update_file_int( string FH_Name, int val );
    char *read_file( string FH_Name );
private:
    string FH_Name;
    long lSize;
    char * buffer;
};
#endif
