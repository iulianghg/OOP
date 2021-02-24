// database.h

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdint.h>

// Define the database dimensions
#define DATABASE_COLS 16	// number of colums in row of the databse
#define DATABASE_ROWS 20	// number of rows in the database

// This is the database - it is just a 2D array of values
// that are to be processed one row at a time
extern int8_t Database[][DATABASE_COLS];

#endif