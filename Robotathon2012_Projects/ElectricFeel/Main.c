#include "inc/hw_types.h"		// tBoolean
#include "RASDemo.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/uart.h"		// input/output over UART
#include "RASLib/init.h"



int main(void)
{	
	//Initialize the microcontroller	  	 
	LockoutProtection();
	InitializeMCU();
	initUART();
	UARTprintf("Hello\n");
	
	//Initialize the hardwares
	InitializeMotors(false, true);
	InitializeEncoders(false, true);
	InitializeLineSensor();
	SetDischargeTime(350);

	//DeadReckoning();
	//LineFollower();
	//WallFollower();
	//FigureEight();
	//SquareDance();
	ObjectFinder();
}
	