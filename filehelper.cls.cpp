//
//  filehelper.cls.cpp
//  QuadCopter
//
//  Created by Michael Brookes on 30/03/2015.
//  Copyright (c) 2015 Michael Brookes. All rights reserved.
//

#include "headers/filehelper.cls.h" //header file for this class.

FileHelper::FileHelper() {
    
}

/*!
 @function file_exists
 - A simple function call to check if a file exists or not.
 @public Available to other objects that initialise this class.
 @param FH_NAME<string> The full path to this file.
 @return Boolean 1 success, 0 failure
 */
int FileHelper::file_exists(string FH_Name){
    FILE * aFile;
    const char *file_name = FH_Name.c_str();
    aFile = fopen(file_name , "rb");
    if (aFile!=0) //if aFile is not 0 it has found the file.
        return 1; //return true (1)
    else
        return 0; //nothing was found. No file exists.
}

/*!
 @function update_file_int
 - Empties a file and then writes and integer into that file.
 @public Available to other objects that initialise this class.
 @param FH_NAME<string> The full file path to open and write to
 @param val<int> The integer value to write into this file.
 @return Boolean 1 success, 0 failure
 @throws Exception
 */
int FileHelper::update_file_int(string FH_Name, int val){
    FILE * bFile; //file handle
    int i; //for loop counter;
    char buf[16] = {0}; //buffer array.
    const char *file_name = FH_Name.c_str(); //convert the string FH_Name to char
    try { //try catch for exceptions.
        for(i = 1; i <= 3; i++){ //start the loop
            bFile = fopen(file_name, "rb"); //attempt to open the file for reading.
            if (bFile == NULL) { //if NULL then the file doesn't exist - we are going to take 3 attempts.
                cout << "Unable to write : " << val << " to file : " << FH_Name << " | attempt " << i << endl;
            }//end if
            else{
                fclose(bFile); //close the file (opened for reading)
                bFile = fopen(file_name, "w"); //reopen the file for writing as we know if exists if we arrived here.
                fprintf(bFile, "%d", val); //print to the file
                fclose(bFile); //close the file
                i = 4; //exit loop
            }//end else
            if(i != 4)
                sleep(1); //wait 1 second before the next attempt.
        } //end for
    } catch (int e) { //catch an exception
        cout << "an exception occurred. " << e << endl; //print the exception for the user.
        return 0; //return error
    } //end try / catch
    return 1; //if we get here, return success.
}

char * FileHelper::read_file( string FH_Name ){
    FILE * aFile;
    buffer = 0;

    aFile = fopen(FH_Name.c_str(), "rb");
    if (aFile == NULL){	fputs(FH_Name.c_str(), stderr); exit(1);}

    fseek(aFile, 0, SEEK_END);
    lSize = ftell(aFile);
    rewind(aFile);

    buffer = (char*) malloc(sizeof(char)*lSize);
    if(buffer == NULL) {fputs("Memory error", stderr); exit(2);}

    fread(buffer, 1, lSize, aFile);
    fclose(aFile);
    
    return buffer;
}