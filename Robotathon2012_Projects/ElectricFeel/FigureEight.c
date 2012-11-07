#include "inc/hw_types.h"		// tBoolean
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "RASLib/encoder.h"

#include "RASDemo.h"

void FigureEight(void) {
	long encoder0;
	long encoder1;
	long encoder0Limit = 0;
	long encoder1Limit = 0;

	GetEncoderCounts(&encoder0, &encoder1);

	while(1) {
	UARTprintf("hello");
	
	SetMotorPowers(120, 60);

	GetEncoderCounts(&encoder0, &encoder1);
	encoder1Limit = encoder1 + 20000;

	while(encoder1 < encoder1Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
		UARTprintf("%d    %d      %d    %d\n", encoder1, encoder1Limit, encoder0, encoder0Limit);
	}

	SetMotorPowers( 60, 120);
	
	GetEncoderCounts(&encoder0, &encoder1);
	
	encoder0Limit = encoder0 + 200000;

	while(encoder0 < encoder0Limit) {
		GetEncoderCounts(&encoder0, &encoder1);
	}
	}
}


	