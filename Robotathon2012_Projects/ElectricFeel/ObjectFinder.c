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

void InitAdcPorts(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);
	ADCSequenceConfigure(ADC_BASE,0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC_BASE, 0, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC_BASE, 0, 2, ADC_CTL_CH2);
	ADCSequenceStepConfigure(ADC_BASE, 0, 3, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceEnable(ADC_BASE, 0);
}

long sampleAdcPort(int port) {
	unsigned long ADCValues[4] = {0};
	ADCProcessorTrigger(ADC_BASE, 0 ); 
	while(!ADCIntStatus(ADC_BASE, 0, false)); 
	ADCSequenceDataGet(ADC_BASE, 0, ADCValues);
	ADCIntClear(ADC_BASE, 0);
	return ADCValues[port];
}

long convertAdc(long x){
	return (((6000*1000) / x) - 6000)/100;
}




void turnLeft(void) {
	SetMotorPowers(-100, 120);
	Wait(760);
}

void ObjectFinder(void) {
	long adcSample;
	long distance;

	//unsigned long waitTime = 500;
	adcSample = sampleAdcPort(0);

	while(1) {
		long limit = 0;
		long count = 0;

		SetMotorPowers(90, 97);
		while(count < limit) {
			Wait(100);
			adcSample = sampleAdcPort(0);
			distance = convertAdc(adcSample);
			if(distance < 100) {
				SetMotorPowers(0,0);
				return;
			}
			count++;
		}
		limit += 6;
		turnLeft();
	}
	
//	while(1) {
//		SetMotorPowers(90, 97);
//		Wait(waitTime);
//		waitTime += 600;
//		turnLeft();
//	}
}
