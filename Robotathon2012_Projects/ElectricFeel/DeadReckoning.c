#include "inc/hw_types.h"		// tBoolean
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "RASLib/encoder.h"

#include "RASDemo.h"

void DeadReckoning (void) {

	signed long encoder0 = GetEncoderCount(ENCODER_0);	//Read encoder values	 
	signed long encoder1 = GetEncoderCount(ENCODER_1);
	
	signed long encoder0Limit = 200000;	//Set encoder limits to exit out of while loop
	signed long encoder1Limit = 200000;
	
	SetMotorPowers(90, 93);		//Set motor to go straight

	while(encoder0 < encoder0Limit && encoder1 < encoder1Limit) {	//Keep going straight while encoder values are smaller than the limits
		GetEncoderCounts(&encoder0, &encoder1);		//Keep reading encoder values
	}

	SetMotorPowers(120, 50);	//Set motor to turn
	
	encoder0Limit += 200000;

	while(encoder0 < encoder0Limit) {	//Keep turning
		GetEncoderCounts(&encoder0, &encoder1);
	}
	
	SetMotorPowers(90, 90);		//Set motor to go straight
	encoder0Limit += 150000;
	encoder1Limit += 150000;
	while(encoder0 < encoder0Limit && encoder1 < encoder1Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
	}
	SetMotorPowers(0, 0);	//Stop
}
