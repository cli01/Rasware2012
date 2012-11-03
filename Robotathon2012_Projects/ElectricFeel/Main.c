#include "inc/hw_types.h"		// tBoolean
#include "RASDemo.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/uart.h"		// input/output over UART
#include "RASLib/init.h"



int main(void)
{		  	 
	LockoutProtection();
	InitializeMCU();
	initUART();
	UARTprintf("Hello\n");
	
	InitializeMotors(false, true);
	InitializeEncoders(false, true);
	InitializeLineSensor();
	SetDischargeTime(350);
	SetMotorPowers(80, 80);

	//DeadReckoning();
	LineFollower();
}
	