// Results.h

#ifndef _RESULTS_H_
#define _RESULTS_H_

#include "database.h"
#include <stdint.h>

// Access an area of memory that holds the results of the processing
// A 'Results' object has the following member functions
//  Results - a constructor function to define storage location of results
//  StoreResult - put an item in the data store
//  EmptyResults - reset to point to the start of the data store
//  ConsumeResult - consume an item from the data store
// A 'Results' object has the following members
//  Data - space to store results of processing each row
//  number - current entry being accessed in the 'Data' data store
//	head - beginning of memory 
//	tail - end of memory
class Results {
 public:
	Results() {number = 0;}      // initial location is the start of the 'Data' data store
	void StoreResult(int32_t);   
  void EmptyResults();        
	int32_t ConsumeResult();
 private:
	int32_t Data[DATABASE_ROWS];  
  uint32_t number; 
	uint32_t head;							
	uint32_t tail;								 
};

#endif