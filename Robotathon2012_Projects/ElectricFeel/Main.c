#include "inc/hw_types.h"		// tBoolean
#include "RASDemo.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/uart.h"		// input/output over UART
#include "RASLib/init.h"



int main(void)
{	
	char right = 10, left = 10;
	int lsArray[8];
	unsigned char lsByte;
	long* eCountRight;
	long* eCountLeft;	  	 
	LockoutProtection();
	InitializeMCU();
	initUART();
	UARTprintf("Hello\n");
	
	InitializeMotors(false, true);
	InitializeEncoders(false, true);
	InitializeLineSensor();
	SetMotorPowers(right, left);
	SetDischargeTime(240);
	SetMotorPowers(60, 60);
	
//	while(*eCountRight < 500000 && *eCountLeft < 500000) {
//		GetEncoderCounts(eCountRight, eCountLeft);
//	}
//	
//	PresetEncoderCounts(0,0);
//	
//	SetMotorPowers(50, 120);
//	
//	while(*eCountLeft < 1000) {
//		GetEncoderCount(eCountLeft);
//	}
//	
//	PresetEncoderCounts(0,0);
//	
//	SetMotorPowers(60, 60);
//	
//	while(*eCountRight < 100000 && *eCountLeft < 100000) {
//		GetEncoderCounts(eCountRight, eCountLeft);
//	}
//	
//}


		while(1) {
		int sum = 0;
		int lsArray[8];
		unsigned char lsByte = ReadLineSensor();
		unsigned char temp;
		int i;
		int k;
		int l;
		int count;
		int j = -3;

		for(i = 0; i < 8; i++) {
		 	temp = ~lsByte;
			lsArray[i] = (temp & 0x01);
			lsArray[i] = j * lsArray[i];
			lsByte = lsByte >> 1;
			j++;
		}

		for(k = 0; k < 8; k++) {
			sum += lsArray[k];
		}
		
		if (sum < 0) {
			left = 30 + (-1) * sum * 9;
			right = 30 - sum * 3;
		}

		if (sum > 0) {
			right = 30 + sum * 10;
			left = 30 - sum * 3;
		}

		if (sum == 0) {
			left = 40;
			right = 40;
		}
		
		SetMotorPowers(right, left);
		
		if (count % 100 == 0) {
			for(l = 0; l < 8; l++) {
				UARTprintf("%d", lsArray[l]);
			}
			UARTprintf("    ");
			UARTprintf("%d\n", sum);
		}
		
		count++;
	}
}