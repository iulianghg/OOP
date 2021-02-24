// LEDs.cpp

#include "LEDs.h"
extern "C" { 
	#include "gpio_setup.h"  // set up input/output ports and interrupts
}

// Configure an LED by connecting to a specific pin
// Arguments: the bit pattern mask specifying the LED pin
// Return: nothing
LEDs::LEDs(uint16_t _bit_pattern) {
	bit_pattern = _bit_pattern;
	off();
}

// Turn on an LED
// Arguments: none
// Return: nothing
void LEDs::on()
{
  GPIOE->ODR = GPIOE->ODR | (uint16_t) bit_pattern;
}

// Turn off an LED
// Arguments: none
// Return: nothing
void LEDs::off()
{
  GPIOE->ODR = GPIOE->ODR & ~((uint16_t) bit_pattern);
}

// Toggle an LED 
// Arguments: none
// Return: nothing
void LEDs::toggle()
{
  GPIOE->ODR = GPIOE->ODR ^ ((uint16_t) bit_pattern);
}
