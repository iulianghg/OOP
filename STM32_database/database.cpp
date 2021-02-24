// database.cpp

#include "database.h"

// This is the database - it is just a 2D array of values
// that are to be processed one row at a time
int8_t Database[][DATABASE_COLS] = {
  { 83,-37, 55, 16,-44, 65, 51, 91, -7, 74,-82,-84, 24,-29,  8,-76},
  { -7,-74, 82, 84, 24, 29, -8, 76, 89, 57, 25,  2, 62, 73, 24, 44}, 
  {  7,-74, 82,-84, 24,-29,  8,-76, 89, 57,-25,  2,-62, 73,-24, 44},
  {-89,-57,-25,  2, 62, 73, 24, 44, 89, 57, 25,  2, 62, 73, 24, 44}, 
  { 89, 57, 25, -2,-62,-73, 24,-44,-89, 57,-25,  2, 62, 73, 24, 44},
  { 30, 23, 85, 38, 61,  5, 59,-37, 74,-84, 23,-71, 61,-66, 45,  5}, 
	{ 30,-23, 85,-38, 61,  5, 59, 37, 74, 84, 23, 71,-61,-66, 45,  5},
  { 74, 84, 23,-71, 61, 66, 45,  5,  2, 56,-55, 10,-11,-42,-82,-50}, 
  { 74,-84, 23,-71,-61, 66,-45,  5,- 2, 56,-55, 10,-11, 42,-82, 50},
  {- 2, 56,-55, 10, 11, 42, 82, 50, 97,  5, 28, 91, 80, 23, 68, 34}, 
  {  2, 56,-55, 10,-11, 42,-82, 50,-97,  5, 28, 91, 80,-23, 68, 34},
  {-97,  5, 28,-91, 80, 23, 68,-34, 16,-45, 66,-57, 55, 49, 51, 85}, 
  { 97,  5,-28, 91,-80, 23,-68, 34,-16, 45,-66, 57,-55, 49,-51, 85},
  {-16, 45,-66, 57,-55, 49, 51, 85, 16, 17, 70, 31, 75, 93, 68, 98}, 
  { 16, 45,-66, 57,-55, 49,-51, 85,-16, 17,-70, 31,-75, 93,-68, 98},
  { 16, 17, 70, 31, 75, 93, 68, 98, 77,-48, 69, 29,-50, 95,-51,  2}, 
  { 16, 17,-70, 31,-75, 93,-68, 98,-77, 48,-69, 29,-50, 95, 51,  2},
  {  7, 48, 69,-29, 50, 95,-51,  2,  4,-77,  1,-16, 17, 94, 50, 38}, 
  { 77, 48, 69, 29,-50, 95,-51,  2,- 4, 77,- 1, 16,-17, 94, 50, 38},
  {  4, 77,  1, 16, 17,-94, 50, 38,-77, 14,-13, 90,-60,  1,-62, 98}
};
