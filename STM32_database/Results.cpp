// Results.cpp

#include "Results.h"

// Add a result to the next location in memory
// Arguments: the value to add to the memory area
// Return: nothing
void Results::StoreResult(int32_t res) {
	Data[number] = res;
	number++;
	tail = (tail + 1) % DATABASE_ROWS;
}

// Empty by just going back to start of the buffer
// Arguments: none
// Return: nothing
void Results::EmptyResults() {
	number = 0;
	tail = 0;
	head = 0;
}

// Consume a result from memory
// Arguments: none
// Return: the value added to the memory area
int32_t Results::ConsumeResult()
{
	int32_t res = Data[head];
	number--;
	head = (head + 1) % DATABASE_ROWS;
	return res;
}
