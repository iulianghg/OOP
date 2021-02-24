// LEDs.h

#ifndef _LEDS_H_
#define _LEDS_H_

#include <stdint.h>

// Specify LED actions and access through a bit pattern mask
// An 'LEDs' object has the following member functions
//  LEDs - a constructor function to set up bit pattern mask
//  on - turn on selected LED
//  off - turn off selected LED
//  toggle - toggle selected LED
// An 'LEDs' object has the following members
//  bit_pattern - the bit pattern mask specifying the LED pin
class LEDs {
	public:
	  LEDs (uint16_t);   // set up the bit pattern mask specifying the LED pin 
  	void on();
    void off();
    void toggle();
	private:
		uint16_t bit_pattern; 
};

#endif