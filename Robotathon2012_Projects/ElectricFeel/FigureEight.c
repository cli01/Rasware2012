#include "inc/hw_types.h"		// tBoolean
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "RASLib/encoder.h"

#include "RASDemo.h"

void FigureEight(void) {
	while(1) {
	SetMotorPowers(120, 90);	//Make top half of figure eight
	Wait(8400);					
	SetMotorPowers(80, 120);	//Make bottom half of figure eight
	Wait(8500);
	}
}
	