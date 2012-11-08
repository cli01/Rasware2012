#include "inc/hw_types.h"		// tBoolean
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"	// input/output over UART
#include "driverlib/uart.h"		// input/output over UART
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "driverlib/adc.h"
#include "RASLib/adc.h"
#include "RASLib/encoder.h"

#include "RASDemo.h"

//void InitAdcPorts(void) {
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
//	ADCSequenceConfigure(ADC_BASE,0, ADC_TRIGGER_PROCESSOR, 0);
//	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_CH0);
//	ADCSequenceStepConfigure(ADC_BASE, 0, 1, ADC_CTL_CH1);
//	ADCSequenceStepConfigure(ADC_BASE, 0, 2, ADC_CTL_CH2);
//	ADCSequenceStepConfigure(ADC_BASE, 0, 3, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);
//	ADCSequenceEnable(ADC_BASE, 0);
//}
//
//long sampleAdcPort(int port) {
//	unsigned long ADCValues[4] = {0};
//	ADCProcessorTrigger(ADC_BASE, 0 ); 
//	while(!ADCIntStatus(ADC_BASE, 0, false)); 
//	ADCSequenceDataGet(ADC_BASE, 0, ADCValues);
//	ADCIntClear(ADC_BASE, 0);
//	return ADCValues[port];
//}
//
//long convertAdc(long x){
//	return (((6000*1000) / x) - 6000)/100;
//}

void WallFollower(void) {
	long encoder0Limit = 0;
	long encoder1Limit = 0;
	long adcSample1;
	long distance1;
	long adcSample2;
	long distance2;
	long encoder0 = 0;
	long encoder1 = 0;
	GetEncoderCounts(&encoder0, &encoder1);

	InitAdcPorts();

	while(1) {
		//Sample ADC ports and convert accordingly
		adcSample1 = sampleAdcPort(0);
		distance1 = convertAdc(adcSample1);
		adcSample2 = sampleAdcPort(2);
		distance2 = convertAdc(adcSample2);

		GetEncoderCounts(&encoder0, &encoder1);	//Update encoder values

		if(distance1 > 300) {			//If the side of the robot is very far from the wall, make a sharp turn
			SetMotorPowers(120, 60);
			encoder0Limit += 16000;
			while(encoder0 < encoder0Limit) {
				GetEncoderCounts(&encoder0, &encoder1);
			}
		} else if(distance1 > 120) {	//If the robot is veering away from the wall, slightly turn toward the wall
			SetMotorPowers(70, 30);
		} else if(distance1 < 40) {		//If the robot is too close to the wall, slightly turn away
			SetMotorPowers(30, 70);
		} else {
			SetMotorPowers(70, 70);		//Go straight otherwise
		}

		if(distance2 < 100) {			//If the front of the robot is close to the wall, make a sharp turn
			SetMotorPowers(-20, 120);
			encoder1Limit += 100000;
			while(encoder1 < encoder1Limit) {
				GetEncoderCounts(&encoder0, &encoder1);
			}
		}
	}
}
