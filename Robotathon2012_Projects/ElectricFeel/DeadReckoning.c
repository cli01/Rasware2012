#include "inc/hw_types.h"		// tBoolean
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "RASLib/encoder.h"

#include "RASDemo.h"

void DeadReckoning (void) {

	signed long encoder0 = GetEncoderCount(ENCODER_0);	 
	signed long encoder1 = GetEncoderCount(ENCODER_1);
	signed long encoder0Limit = 200000;
	signed long encoder1Limit = 200000;

	while(encoder0 < encoder0Limit && encoder1 < encoder1Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
		//UARTprintf("%d    %d\n", encoder0, encoder1);
	}
	//UARTprintf("%d    %d\n", encoder0, encoder1);	
	//UARTprintf("\n\n\n\nTurrrnnnn\n");
	//PresetEncoderCount(ENCODER_0, 0);
	//PresetEncoderCount(ENCODER_1, 0);
	SetMotorPowers(120, 50);
	
	encoder0Limit += 200000;
	while(encoder0 < encoder0Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
		//UARTprintf("%d    %d\n", encoder0, encoder1);
	}
	
	//PresetEncoderCount(ENCODER_0, 0);
	//PresetEncoderCount(ENCODER_1, 0);
	
	SetMotorPowers(90, 90);
	//UARTprintf("Goooooooooooooooo\n");
	//UARTprintf("%d    %d\n", encoder0, encoder1);
	encoder0Limit += 150000;
	encoder1Limit += 150000;
	while(encoder0 < encoder0Limit && encoder1 < encoder1Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
		//UARTprintf("%d    %d\n", encoder0, encoder1);
	}
	SetMotorPowers(0, 0);
}