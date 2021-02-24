// -------------------------------------------------------------------------------
// Name:        STM32F Discovery Board
//
// Author:      Julian Gherghel
// -------------------------------------------------------------------------------
//
// This program is designed for the STM32 Discovery target board 

// Purpose 
// This program obtains data from a small database to simulate
// data received from an external device and processes the data.
// The data processing operation is repeated precisely every 250ms
// but it can be slowed to every 500ms when the user button is
// pressed. When processing speed is slowed, two red LEDs on the
// board will light up.
// The results are stored in a location in memory and they are
// deleted from memory every 250ms to simulate removal to an
// external device. The speed of deletion is slowed down to 500ms
// when the data processing speed is slowed. Two green LEDs will
// be toggled at each deletion.

// Limitation
// For the purpose of this simulation, the dimension of the database
// is limited to 20 rows and 16 columns.

#include "database.h"
#include "Process.h"
#include "Results.h"
#include "LEDs.h"
// Configuration of the STM32 Discovery board
extern "C" { 
	#include "gpio_setup.h"	// set up input/output ports and interrupts
} 

// Timer interrupt frequency speed settings
#define DELAY_DEF 2000000 // 250 ms
#define DELAY_SLW (2 * DELAY_DEF) // 500 ms

// Number of LEDs on the board
#define NUM_LEDs 8

// Define the LEDs
LEDs LED[NUM_LEDs] = {LED8,LED6,LED4,LED3,LED5,LED7,LED9,LED10};

// Interrupt Service Routine called when button pressed
void HAL_GPIO_EXTI_Callback(uint16_t); 

// Indicates when input is received
volatile bool IP_flag = false;

// Indicates when data processing is taking place
volatile bool PR_flag = false;

// Define objects for processing the database values and storing
// the results of the calculations
Process P(*Database);
Results R;
	
// Perform an example run of the processing and then run a loop to light LEDs
// and adjust processing speed according to User Button presses
int main(void)
{
	// Initialize the GPIO for the input/output of ports and set up interrupts
	gpio_setup();
	
  // Timer interrupt frequency in microseconds (do not exceed 0xFFFFFF microseconds)
  SysTick_Config(DELAY_DEF);
	
	// Keep the program running in an infinite loop
	while (true) 
	{
		// Toggle green LEDs as data is deleted 
		if (PR_flag == true) 
		{
			P.NextRow();
			R.StoreResult(P.ProcessRow());
			R.ConsumeResult();
			LED[1].toggle();
			LED[5].toggle();
			PR_flag = false;
		}
	}
}	

// Interrupt service routine for handling Port A interrupts
// Arguments: the pin generating the input
// Return: nothing
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)	// Check the user button has generated the interrupt
		{	
		IP_flag = !IP_flag;
		// Turn ON red LEDs at top of board and change processing speed to 500ms
		// when the User Button is pressed
		if (IP_flag) 	
		{
			LED[3].on();
			LED[7].on();
			SysTick_Config(DELAY_SLW);
		}
		// Turn OFF red LEDs at top of board and change processing speed to 250ms
		// when the User Button is pressed again
		else
		{
			LED[3].off();
			LED[7].off();
			SysTick_Config(DELAY_DEF);
		} 
  }
}

// This function handles the system tick timer interrupt
// Arguments : none
// Return: nothing 
void SysTick_Handler(void)
{
	PR_flag = true;
}
