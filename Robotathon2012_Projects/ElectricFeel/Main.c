#include "inc/hw_types.h"		// tBoolean
#include "RASDemo.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/uart.h"		// input/output over UART
#include "RASLib/init.h"



int main(void)
{	
	char right = 0, left = 0;
	unsigned char lineByte = 0;
	int lineSensorArray[8];
	int i; 	  	 
	LockoutProtection();
	InitializeMCU();
	initUART();
	
	InitializeMotors(false, false);
	InitializeLineSensor();
	SetDischargeTime(/*Insert Here*/);
	
	while(1) {
	lineByte = 	ReadLineSensor();
	
	for(i = 0; i < 8; i++) {
		lineSensorArray[i] = lineSensorByte & 0x01;
		lineSensorByte = lineSensorByte >> 1;
	}
}
