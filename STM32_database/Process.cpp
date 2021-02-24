// Process.cpp

#include "Process.h"
#include "database.h"
#include <cmath>

// Set up a pointer to the database and start at row 0
// Arguments: the start of the database values
// Return: nothing
Process::Process(int8_t* DB) {
	database = DB;
	row = database;
}

// Processing of one row of the database
// Arguments: none
// Return: a single value that is the output of all the processing
int32_t Process::ProcessRow() {
	int32_t sum = 0;
	for(uint32_t i=0;i<DATABASE_COLS;i++) {
	  for(uint32_t j=i;j<DATABASE_COLS;j++) {		
		  sum += sqrt(row[i]*row[1] + row[j]*row[j]);
		}
	}
	return sum;
}

// Read database rows in a circular manner
// Arguments: none
// Return: nothing
void Process::NextRow() {
	row = row + DATABASE_COLS;
  if (row >= database + DATABASE_ROWS*DATABASE_COLS) {
		row = database;
	}
}

// Process all the rows of the database
// Arguments: none
// Return: the final total of all the processing
int32_t Process::ProcessAll() {
	int32_t total = 0;
	for(uint32_t i=0;i<DATABASE_ROWS;i++) {
		total += ProcessRow();
		NextRow();
	}
	return total;
}
