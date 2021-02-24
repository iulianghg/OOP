// Process.h

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <stdint.h>

// Carry out simple processing of data obtained from the database
// A 'Process' object has the following member functions
//  Process - a constructor function to initialize the addresses 
//  pointing to the database
//  ProcessRow - data processing of the current row
//  NextRow - change 'row' to point to the next database row
//  ProcessAll - data processing of all the rows in turn
// A 'Process' object has the following members
//  database - address of the start of the database
//	row - address of current database row being processed
class Process {
 public:
	Process(int8_t*);      
	int32_t ProcessRow(); 
  void NextRow();       
 	int32_t ProcessAll();   
 private:
	int8_t* database; 
  int8_t* row;       
};

#endif
