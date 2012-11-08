//#include "inc/hw_types.h"		// tBoolean
//#include "inc/hw_memmap.h"
//#include "utils/uartstdio.h"	// input/output over UART
//#include "driverlib/uart.h"		// input/output over UART
//#include "driverlib/gpio.h"
//#include "driverlib/sysctl.h"
//
//#include "driverlib/adc.h"
//#include "RASLib/adc.h"
//#include "RASLib/encoder.h"
//
//#include "RASDemo.h"
//
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


void SquareDance(void) {
//	long adcSample;
//	long distance;
//
//	InitAdcPorts();
//	SetMotorPowers(90, 106);
//	adcSample = sampleAdcPort(0);

	while(1) {
//		adcSample = sampleAdcPort(0);
//		distance = convertAdc(adcSample);

		SetMotorPowers (90, 106);	//Go in a straight line
		Wait (3650);
		SetMotorPowers (110, 20);	//Turn
		Wait (550);
		
//		if (distance < 100) {
//			//Wait(2500);
//			//UARTprintf("%d\n", distance);
//			SetMotorPowers(120, 20);
//			Wait(550);
//			SetMotorPowers(94, 90);
//			Wait(2000);
	}
}
